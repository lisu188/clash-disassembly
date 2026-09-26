import struct
BASE_IMAGES=tuple(bytes((i*37+seed*13)&255 for i in range(800)) for seed in range(256))
TYPES=(-32768,-257,-2,-1,0,1,30,31,32,33,34,35,255,32767)
BASES=(0x30000020,0x7ffffef0,0x80000020,0x90000020)
def row(mode,base,prefix,flags,kind=1,marker=-1):
 image=bytearray(BASE_IMAGES[flags&255])
 for i in range(10):
  struct.pack_into('<h',image,38+31*i,31 if i<prefix else -1 if i==prefix else 33)
  image[51+31*i]=(flags+17*i)&255
 if marker>=0:struct.pack_into('<h',image,38+31*marker,kind)
 return struct.pack('<II',mode,base)+image
def cases():
 for mode in (1,2):
  for base in BASES:
   for prefix in range(11):
    for flags in range(256):yield row(mode,base+(flags&15),prefix,flags)
  for alignment in range(16):
   for prefix in range(11):
    for marker in range(10):
     for kind in TYPES:yield row(mode,BASES[alignment&3]+alignment,prefix,kind&255,kind,marker)
  for prefix in range(11):
   for delta in (-2,-1,0,1,2):
    for flags in (0,1,2,3,127,128,254,255):yield row(mode,0x80000000-6-31*prefix+delta,prefix,flags)
def expected(data,pointer_bytes=4):
 mode,base=struct.unpack_from('<II',data);image=bytearray(data[8:]);processed=0
 for i in range(10):
  if struct.unpack_from('<h',image,38+31*i)[0]==-1:break
  if mode==1:image[51+31*i]|=2
  else:image[51+31*i]&=253
  processed+=1
 result=(base+6+31*processed)&0xffffffff
 return result.to_bytes(pointer_bytes,'little')+image
