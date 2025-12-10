#if 0
read -r -d '' r << EOF
import inspect
import sys
import resource
import operator
import os
LIMIT = operator.floordiv(os.sysconf("SC_PAGE_SIZE") * os.sysconf("SC_PHYS_PAGES"),16)
resource.setrlimit(resource.RLIMIT_STACK, (8*LIMIT,-1))
sys.setrecursionlimit(LIMIT)
sys.set_int_max_str_digits(LIMIT)
def r(*xs):
  l = len(xs)
  if l==0: return 0
  if l==1: return xs[0]+1
  n = int(xs[0]) if l>0 else 0
  a = int(xs[1]) if l>1 else 0
  b = int(xs[2]) if l>2 else 0
  frame = inspect.currentframe().f_back
  caller_locals = frame.f_locals
  caller_args = [frame.f_locals[arg_name] for arg_name in frame.f_code.co_varnames[:frame.f_code.co_argcount]]
  if n==0: return caller_args[a]
  if n==1 and caller_args[0]>a: return globals().get(frame.f_code.co_name)(*xs[1:])
  if n==1: return 0
  if n==2: return operator.floordiv(a,b) if b else 0 # return a//b if b else 0
  if n==3: return a-b if a>b else 0
  if n==4: return b+1
  if n==5: return a+b
  if n==6: return a*b
  if n==7: return a**b
  if n > 6 and b==0: return 1
  return r(n-1,a,r(n,a,b-1))
def _main():
  def _toN(x):
    try:
      return int(x,0)
    except:
      return 0
  funcs = []
  for name, obj in globals().items():
    if inspect.isfunction(obj):
      funcs.append((obj.__code__.co_firstlineno, obj))
  if not funcs:
    return None
  funcs.sort(key=lambda x: x[0])
  main = funcs[-1][1]
  return main(*[_toN(sys.argv[i+1]) if i < len(sys.argv)-1 else 0 for i,x in enumerate([0]*len(inspect.signature(main).parameters))])
#define if(a,b,c) ((b) if (a) else (c))
#define fn(name,body) def name: return body
EOF
gcc -E -x c -P <(echo "$r"; cat $0; echo -e "print(_main())") |
python3 - "$@"
exit
#endif

fn(div(a,b),r(2,a,b))
fn(tsb(a,b),r(3,a,b))
fn(inc(a),  r(4,a,a))
fn(add(a,b),r(5,a,b))
fn(mul(a,b),r(6,a,b))
fn(pow(a,b),r(7,a,b))
fn(hyp(n,a,b),r(add(n,4),a,b))

fn(dec(a),tsb(a,1))
fn(Not(a),tsb(1,a))
fn(isZero(a),Not(a))
fn(isNonZero(a),Not(isZero(a)))
fn(If(a,b,c),add(mul(isNonZero(a),b),mul(isZero(a),c)))
fn(Or(a,b),isNonZero(add(a,b)))
fn(And(a,b),isNonZero(mul(a,b)))
fn(eq(a,b),isZero(add(tsb(a,b),tsb(b,a))))
fn(lte(a,b),isZero(tsb(a,b)))
fn(lt(a,b),And(lte(a,b),Not(eq(a,b))))
fn(gt(a,b),Not(lte(a,b)))
fn(gte(a,b),Not(lt(a,b)))
fn(min(a,b),if(lt(a,b),a,b))
fn(max(a,b),if(lt(a,b),b,a))
fn(rem(a,b),tsb(a,mul(b,div(a,b))))
fn(isDivisible(a,b),isZero(rem(a,b)))
fn(isEven(a),isDivisible(a,2))
fn(isOdd(a),Not(isEven(a)))
fn(mag(a),div(a,a))
fn(ack(m,n),if(m,tsb(hyp(m,2,add(n,3)),3),inc(n)))

fn(_root_mid(l,h),div(inc(add(l,h)),2))
fn(_root(n,a,b,l,h),if(gte(l,h),l,if(lte(pow(_root_mid(l,h),b),a),r(1,dec(n),a,b,_root_mid(l,h),h),r(1,dec(n),a,b,l,dec(_root_mid(l,h))))))
fn(root(a,b),_root(a,a,b,0,a))

fn(_mytsb(b,a),if(b,dec(r(1,dec(b),a)),a))
fn(mytsb(a,b),_mytsb(b,a))

fn(_mydiv(b,n,d,q),if(lt(b,d),q,r(1,tsb(b,d),n,d,inc(q))))
fn(mydiv(a,b),_mydiv(a,a,b,0))

fn(_mypow(b,a),if(eq(b,0),1,if(eq(b,1),a,mul(a,r(1,dec(b),a)))))
fn(mypow(a,b),_mypow(b,a))

fn(_isPrime(i,n),if(lt(i,2),1,if(isDivisible(n,i),0,r(1,dec(i),n))))
fn(isPrime(n),if(n,_isPrime(dec(n),n),0))

fn(gcd(a,b),if(b,r(1,b,rem(a,b)),a))

fn(_nthPrime(b,i,n),if(n,if(isPrime(i),r(1,dec(b),inc(i),dec(n)),r(1,dec(b),inc(i),n)),dec(i)))
fn(nthPrime(n),_nthPrime(mul(n,n),2,n))
