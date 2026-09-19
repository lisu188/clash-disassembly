// Boundary-controlled original machine-code oracle. The original regroup body
// executes unmodified. External behavior is scripted identically for both sides.
extern "C" int original_regroup(int,int);
extern "C" { int gameData=0; }
const char *aPrzegrupujar_0="synthetic diagnostic boundary";
static unsigned char worlds[2][4096], expected_worlds[2][4096], path[404], expected_path[404];
static unsigned events[128], expected_events[128], event_count, mode, movement_count, execution_count, active_world, case_id;
static int first_index,second_index,last_row,last_col;
static unsigned seed;
static unsigned random_word(){seed=seed*1664525u+1013904223u;return seed;}
static void event(unsigned a,unsigned b=0,unsigned c=0,unsigned d=0,unsigned e=0) {
  if(event_count+5>128)die(50);
  events[event_count++]=a;events[event_count++]=b;events[event_count++]=c;events[event_count++]=d;events[event_count++]=e;
}
static void set_word(unsigned char*p,short v){p[0]=(unsigned char)v;p[1]=(unsigned char)(v>>8);}
static void rebind() {
  unsigned next=1-active_world;
  for(unsigned i=0;i<4096;++i) worlds[next][i]=worlds[active_world][i];
  active_world=next;gameData=(int)(intptr_t)worlds[next]-147174;
}
extern "C" void hook_log(){event(1);}
extern "C" int hook_move(int index,int row,int col,int delta) {
  event(2,index,row,col,delta);++movement_count;last_row=row;last_col=col;
  if(mode==1 || (mode==3 && movement_count==2))return 0;
  if(mode>=6)rebind();
  for(unsigned i=0;i<404;++i)path[i]=(unsigned char)(case_id+i*7+movement_count);
  return (int)(intptr_t)path;
}
extern "C" void hook_free() {
  event(3,movement_count);
  // The path must already be copied when the original release occurs.
  unsigned index=movement_count==1?first_index:second_index;
  for(unsigned i=0;i<404;++i)if(worlds[active_world][725*index+316+i]!=path[i])die(51);
  for(unsigned i=0;i<404;++i)path[i]=0xed;
}
extern "C" void hook_execute(int index,int force) {
  event(4,index,force);++execution_count;
  if(mode>=6)rebind();
  if(mode==2 || mode==6 || ((mode==4||mode==7)&&execution_count==2)) {
    set_word(worlds[active_world]+725*index,(short)last_row);
    set_word(worlds[active_world]+725*index+2,(short)last_col);
  }
}
extern "C" void hook_kill(int index) {event(5,index);worlds[active_world][725*index+720]^=0x80;}
void Debug_Log(int,char,DWORD,int,...){hook_log();}
_DWORD* Unit_MoveTrackNearTile(int i,int r,int unused,int c,DWORD d){if(unused!=0)die(52);return(_DWORD*)(intptr_t)hook_move(i,r,c,(int)d);}
void j__nfree_(){hook_free();}
void UnitStack_ExecuteQueuedPath(unsigned int i,int force,char,DWORD,double){hook_execute(i,force);}
int UnitStack_KillByIndex(int i,char,DWORD,double){hook_kill(i);return 0;}
static void fill(unsigned id) {
  case_id=id;seed=id+0x701528d1u;mode=id%8;first_index=(id/8)%4;second_index=(first_index+1+(id/32)%3)%4;
  if(id>=1024&&id%3==0)second_index=first_index;
  for(unsigned b=0;b<2;++b)for(unsigned i=0;i<4096;++i)worlds[b][i]=(unsigned char)(random_word()>>24);
  for(unsigned i=0;i<404;++i)path[i]=(unsigned char)(random_word()>>24);
  active_world=0;gameData=(int)(intptr_t)worlds[0]-147174;
  int n=(id/8)%121,counts[2]={n%11,n/11};
  for(unsigned which=0;which<2;++which) {
    int index=which?second_index:first_index;unsigned char*p=worlds[0]+725*index;
    short row=(id%19==0)?-32768:(id%23==0?32767:50);
    short col=(id%29==0)?-32768:(id%31==0?32767:51);
    if(which && mode!=0) {row=(short)(row+5);col=(short)(col-7);}
    set_word(p,row);set_word(p+2,col);
    for(int j=0;j<10;++j) {
      set_word(p+6+31*j,(short)(j<counts[which]?j+which*16:-1));
      unsigned health=(random_word()>>24);
      if(id<1024) health=(id+j*37+which*91)%256;
      if(id%11==0)health=7;if(id%13==0)health=8;
      p[6+31*j+9]=(unsigned char)health;
    }
  }
  for(unsigned i=0;i<128;++i)events[i]=0;
  event_count=movement_count=execution_count=0;
}
int main(){
 for(unsigned id=0;id<4096;++id){
  fill(id);int result=UnitStack_RegroupWithOtherStackByHealth(first_index,second_index,(char)0xa9,0x87654321u,0.0);
  unsigned metadata[4]={id,(unsigned)result,active_world,event_count};
  output((const char*)metadata,sizeof(metadata));output((const char*)worlds,sizeof(worlds));output((const char*)path,sizeof(path));output((const char*)events,sizeof(events));
 }return 0;
}
