#!/usr/bin/env python3
from __future__ import annotations
import argparse,csv,hashlib,json,re,time
from concurrent.futures import ThreadPoolExecutor,as_completed
from pathlib import Path
from urllib.error import HTTPError,URLError
from urllib.parse import parse_qsl,quote,urlencode,urlparse,urlunparse
from urllib.request import Request,urlopen

UA="clash-disassembly-research/1.0 (+https://github.com/lisu188/clash-disassembly)"
HOST="clash.y0.pl"
CDX="https://web.archive.org/cdx/search/cdx"
HIGH={".7z",".arj",".bat",".bin",".cfg",".com",".dat",".diff",".doc",".docx",".exe",".ini",".ips",".map",".msi",".patch",".pdf",".rar",".rtf",".txt",".xdelta",".xdelta3",".zip"}

def get(url,timeout=90,retries=3):
    err=None
    for n in range(retries):
        try:return urlopen(Request(url,headers={"User-Agent":UA,"Accept-Encoding":"identity"}),timeout=timeout)
        except (HTTPError,URLError,TimeoutError) as e:
            err=e
            if n+1<retries:time.sleep(2**n)
    raise err

def norm(raw):
    p=urlparse(raw); h=(p.hostname or "").lower()
    if h=="www."+HOST:h=HOST
    q=[(k,v) for k,v in parse_qsl(p.query,keep_blank_values=True) if k.lower() not in {"sid","phpsessid"} and not k.lower().startswith("utm_")]
    return urlunparse(("http",h,re.sub(r"/{2,}","/",p.path or "/"),"",urlencode(sorted(q)),""))

def archive(ts,raw):
    return f"https://web.archive.org/web/{ts}id_/{quote(raw,safe=':/?&=%+#;,~@!$()*[]')}"

def rows():
    params=[("url",HOST),("matchType","domain"),("output","json"),("fl","timestamp,original,mimetype,statuscode,digest,length"),("filter","statuscode:200"),("collapse","urlkey"),("showSkipCount","true"),("lastSkipTimestamp","true")]
    with get(CDX+"?"+urlencode(params)) as r:data=json.loads(r.read().decode())
    if len(data)<2:return []
    head={k:i for i,k in enumerate(data[0])}; grouped={}
    for x in data[1:]:
        try:
            key=norm(x[head["original"]]); grouped.setdefault(key,[]).append(x)
        except Exception:pass
    out=[]
    for key,xs in grouped.items():
        xs.sort(key=lambda x:x[head["timestamp"]]); a=xs[0]
        raw=a[head["original"]]; length=a[head["length"]]
        capture_count=sum(1+(int(x[head["skipcount"]]) if "skipcount" in head and str(x[head["skipcount"]]).isdigit() else 0) for x in xs)
        latest=max((x[head["endtimestamp"]] if "endtimestamp" in head and x[head["endtimestamp"]] else x[head["timestamp"]]) for x in xs)
        out.append({"canonical_url":key,"original_url":raw,"first_capture":a[head["timestamp"]],"latest_capture":latest,"capture_count":capture_count,"representative_mimetype":a[head["mimetype"]],"representative_digest":a[head["digest"]],"representative_cdx_length":int(length) if str(length).isdigit() else "","archive_url":archive(a[head["timestamp"]],raw)})
    return sorted(out,key=lambda x:x["canonical_url"])

def candidate(r):
    u=r["canonical_url"].lower(); ext=Path(urlparse(u).path).suffix.lower()
    return ext in HIGH or "deluxe" in u or "/download" in u

def local_path(r,root):
    p=urlparse(r["canonical_url"]); rel=p.path.lstrip("/")
    if not rel or rel.endswith("/"):rel+=("" if not rel or rel.endswith("/") else "/")+"index.html"
    path=Path(rel)
    if p.query:
        q=hashlib.sha1(p.query.encode()).hexdigest()[:10]; path=path.with_name(f"{path.stem}__q_{q}{path.suffix}")
    return root/(p.hostname or HOST)/path

def fetch(r,dst,limit):
    z={"canonical_url":r["canonical_url"],"archive_url":r["archive_url"],"status":"error","bytes":0,"sha256":"","content_type":"","error":""}; tmp=None
    try:
        with get(r["archive_url"],25,2) as h:
            z["content_type"]=h.headers.get("Content-Type",""); cl=h.headers.get("Content-Length","")
            if cl.isdigit() and int(cl)>limit:z["status"]="too_large";return z
            dst.parent.mkdir(parents=True,exist_ok=True); tmp=dst.with_name(dst.name+".part"); dig=hashlib.sha256()
            with tmp.open("wb") as f:
                while True:
                    b=h.read(1024*1024)
                    if not b:break
                    z["bytes"]+=len(b)
                    if z["bytes"]>limit:z["status"]="too_large";return z
                    dig.update(b);f.write(b)
            tmp.replace(dst);tmp=None;z["status"]="downloaded";z["sha256"]=dig.hexdigest();return z
    except Exception as e:z["error"]=f"{type(e).__name__}: {e}";return z
    finally:
        if tmp and tmp.exists():tmp.unlink()

def writecsv(path,data,fields):
    with path.open("w",encoding="utf-8",newline="") as f:
        w=csv.DictWriter(f,fieldnames=fields,extrasaction="ignore");w.writeheader();w.writerows(data)

def plan(inv,maxf,maxt):
    selected=[];skipped=[];reserved=0
    for r in sorted(inv,key=lambda x:(0 if candidate(x) else 1,x["canonical_url"])):
        n=r["representative_cdx_length"] if isinstance(r["representative_cdx_length"],int) else maxf
        if n>maxf:
            skipped.append({"canonical_url":r["canonical_url"],"archive_url":r["archive_url"],"status":"too_large","bytes":0,"sha256":"","content_type":"","error":"CDX length exceeds per-file limit"});continue
        estimate=max(1,n)
        if reserved+estimate>maxt:
            skipped.append({"canonical_url":r["canonical_url"],"archive_url":r["archive_url"],"status":"total_limit","bytes":0,"sha256":"","content_type":"","error":"CDX size budget exhausted"});continue
        selected.append(r);reserved+=estimate
    return selected,skipped

def main():
    p=argparse.ArgumentParser();p.add_argument("--output",default="research/clash_y0");p.add_argument("--mirror-dir");p.add_argument("--max-file-mib",type=int,default=128);p.add_argument("--max-total-mib",type=int,default=512);p.add_argument("--workers",type=int,default=12);a=p.parse_args()
    out=Path(a.output);out.mkdir(parents=True,exist_ok=True); inv=rows(); fields=list(inv[0]) if inv else ["canonical_url","original_url","first_capture","latest_capture","capture_count","representative_mimetype","representative_digest","representative_cdx_length","archive_url"]
    cand=[r for r in inv if candidate(r)];writecsv(out/"inventory.csv",inv,fields);writecsv(out/"download_candidates.csv",cand,fields)
    live=[]
    for u in ["http://clash.y0.pl/","http://clash.y0.pl/download/","http://forum.clash.y0.pl/"]:
        x={"url":u,"status":"","final_url":"","content_type":"","error":""}
        try:
            with get(u,8,1) as h:x.update(status=getattr(h,"status",""),final_url=h.geturl(),content_type=h.headers.get("Content-Type",""))
        except Exception as e:x["error"]=f"{type(e).__name__}: {e}"
        live.append(x)
    (out/"live_status.json").write_text(json.dumps(live,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    results=[];total=0
    if a.mirror_dir:
        root=Path(a.mirror_dir); maxf=a.max_file_mib*1048576; maxt=a.max_total_mib*1048576; selected,skipped=plan(inv,maxf,maxt);results.extend(skipped)
        with ThreadPoolExecutor(max_workers=max(1,a.workers)) as pool:
            futures={pool.submit(fetch,r,local_path(r,root),maxf):r for r in selected}
            for future in as_completed(futures):results.append(future.result())
        results.sort(key=lambda x:x["canonical_url"]);total=sum(x["bytes"] for x in results if x["status"]=="downloaded")
        writecsv(out/"fetch_results.csv",results,["canonical_url","archive_url","status","bytes","sha256","content_type","error"])
    summary={"generated_utc":time.strftime("%Y-%m-%dT%H:%M:%SZ",time.gmtime()),"unique_url_count":len(inv),"high_value_candidate_count":len(cand),"downloaded_count":sum(x.get("status")=="downloaded" for x in results),"downloaded_bytes":total,"error_count":sum(x.get("status")=="error" for x in results),"deluxe_related_urls":[r["canonical_url"] for r in inv if "deluxe" in r["canonical_url"].lower()],"download_related_urls":[r["canonical_url"] for r in inv if "/download" in r["canonical_url"].lower()]}
    (out/"summary.json").write_text(json.dumps(summary,indent=2,ensure_ascii=False)+"\n",encoding="utf-8");print(json.dumps(summary,ensure_ascii=False));return 0 if inv else 2
if __name__=="__main__":raise SystemExit(main())
