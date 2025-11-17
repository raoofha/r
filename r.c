//; xterm-send "echo -ne \"\\033c\"; clang-16 -o /dev/shm/r -rdynamic -Wno-incompatible-pointer-types-discards-qualifiers -Wno-c2x-extensions -Wno-deprecated-non-prototype -Wno-incompatible-library-redeclaration -Wno-implicit-int $0 && ulimit -s unlimited ; /dev/shm/r" ; exit 1 ;

#include <stdio.h>
#include <dlfcn.h>
#include <stdarg.h>

#define N unsigned _BitInt(1024)
#define _ARG_N(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N
#define COUNT_ARGS(...) _ARG_N(__VA_ARGS__,10,9,8,7,6,5,4,3,2,1)
N printN(N x) { char buf[10000000]; int i = 0;  if(x==0) putchar('0'); while (x > 0) { buf[i] = '0' + (x % 10); x /= 10; i += 1; } while(i--) putchar(buf[i]); putchar('\n'); return 0; }
N __r(N n,N a,N b) { if(n==0) return b?a/b:0; if(n==1) return a>b?a-b:0; if(n==2) return b+1; if(n==3) return a+b; if(n==4) return a*b; if(n > 4 && b==0) return 1; return __r(n-1,a,__r(n,a,b-1)); }
N _r(void* f,N k,N* args)
{
  if(k==0) return 0;
  if(k==1) return args[0]+1;
  if(args[0]) return __r(args[0]-1,args[1],args[2]);
  N arg1 = (*(N*)(((void**)__builtin_frame_address(1))+2));
  if(arg1>args[1]) 
  {
    switch(k)
    {
      case 2: return ((N(*)(N))f)(args[1]);
      case 3: return ((N(*)(N,N))f)(args[1],args[2]);
      case 4: return ((N(*)(N,N,N))f)(args[1],args[2],args[3]);
      case 5: return ((N(*)(N,N,N,N))f)(args[1],args[2],args[3],args[4]);
      case 6: return ((N(*)(N,N,N,N,N))f)(args[1],args[2],args[3],args[4],args[5]);
      case 7: return ((N(*)(N,N,N,N,N,N))f)(args[1],args[2],args[3],args[4],args[5],args[6]);
      case 8: return ((N(*)(N,N,N,N,N,N,N))f)(args[1],args[2],args[3],args[4],args[5],args[6],args[7]);
      //case 9: return ((N(*)(N,N,N,N,N,N,N,N))f)(args[1],args[2],args[3],args[4],args[5],args[6],args[7],args[8]);
    }
  }
  return 0;
}
#define r(...) _r(dlsym(dlopen(NULL, RTLD_NOW),__func__),COUNT_ARGS(__VA_ARGS__),(N[]){__VA_ARGS__})

N div(N a,N b) { return r(1,a,b); }
N tsb(N a,N b) { return r(2,a,b); }
N inc(N a)     { return r(3,a,a); }
N add(N a,N b) { return r(4,a,b); }
N mul(N a,N b) { return r(5,a,b); }
N pow(N a,N b) { return r(6,a,b); }
N hyp(N n,N a,N b) { return r(add(n,2),a,b); }

N dec(N a) { return tsb(a,1); }
N not(N a) { return tsb(1,a); }
N isZero(N a) { return not(a); }
N isNonZero(N a) { return not(isZero(a)); }
N _If(N a,N b,N c) { return add(mul(isNonZero(a),b),mul(isZero(a),c)); }
#define If(a,b,c) (a)?(b):(c)
N or(N a,N b) { return isNonZero(add(a,b)); }
N and(N a,N b) { return isNonZero(mul(a,b)); }
N eq(N a,N b) { return isZero(add(tsb(a,b),tsb(b,a))); }
N lte(N a,N b) { return isZero(tsb(a,b)); }
N lt(N a,N b) { return and(lte(a,b),not(eq(a,b))); }
N gt(N a,N b) { return not(lte(a,b)); }
N gte(N a,N b) { return not(lt(a,b)); }

N _root_mid(N l,N h) { return div(inc(add(l,h)),2); }
N _root(N n,N a,N b,N l,N h) { return If(gte(l,h),l,If(lte(pow(_root_mid(l,h),b),a),r(0,dec(n),a,b,_root_mid(l,h),h),r(0,dec(n),a,b,l,dec(_root_mid(l,h))))); }
N root(N a,N b) { return _root(a,a,b,0,a); }

N _mypow(N b,N a) { return If(eq(b,0),1,If(eq(b,1),a,mul(a,r(0,dec(b),a)))); }
N mypow(N a,N b) { return _mypow(b,a); }

main()
{
  printN(r(5,6,7));
  printN(mul(6,7));
  printN(pow(2,10));
  printN(pow(2,30));
  printN(pow(2,40));
  printN(pow(2,50));
  printN(pow(1000,50));
  printN(pow(1000,52));
  printN(pow(9000,3));
  printN(pow(90000,3));
  printN(pow(900000,3));
  printN(pow(9000000,3));
  printN(pow(90000000,3));
  printN(pow(900000000,3));
  printN(pow(9000000000,3));
  printN(mypow(9000,3));
  printN(mypow(90000,3));
  printN(mypow(900000,3));
  printN(mypow(9000000,3));
  printN(mypow(90000000,3));
  printN(mypow(900000000,3));
  printN(mypow(9000000000,3));
  printN(root(0,3));
  printN(root(1,3));
  printN(root(9,3));
  printN(root(27,3));
  printN(root(1000,3));
  printN(root(10000,3));
  printN(root(100000,3));
  printN(root(1000000,3));
  printN(root(10000000,3));
  printN(root(1000000000,3));
  printN(root(10000000000,5));
}
