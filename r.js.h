#if 0
read -r -d '' r << EOF
#define if(a,b,c) (a)?(b):(c)
#define fn(n,b) function n { return b; }
fn(r(n,a,b),if(arguments.length===0,0n,
            if(arguments.length===1,n+1n,
            if(n==0n,r.caller.arguments[a],
            if(n==1n&&(r.caller.arguments[0]>a),r.caller(...Array.from(arguments).slice(1)), 
            if(n==1n,0n,
            if(n==2n,if(b,a/b,0n),
            if(n==3n,if(a>b,a-b,0n),
            if(n==4n,b+1n,
            if(n==5n,a+b,
            if(n==6n,a*b,
            if(n==7n,a**b,
            if(n > 6n && b==0n,1n,
            r(n-1n,a,r(n,a,b-1n)))))))))))))))
EOF
tcc -E -x c -P <(echo "$r"; cat $0; echo "console.log(main(...[...process.argv,...Array(main.length)].slice(2).map((x)=>{try{return BigInt(x);}catch(e){return 0n;}})));") |
node --stack-size=10000000 - "$@"
exit
#endif

fn(inc(a),r(a))
fn(_0(),r())
fn(_1(),inc(_0()))
fn(_2(),inc(_1()))
fn(_3(),inc(_2()))
fn(_4(),inc(_3()))
fn(_5(),inc(_4()))
fn(_6(),inc(_5()))
fn(_7(),inc(_6()))
fn(div(a,b),r(_2(),a,b))
fn(tsb(a,b),r(_3(),a,b))
fn(add(a,b),r(_5(),a,b))
fn(mul(a,b),r(_6(),a,b))
fn(pow(a,b),r(_7(),a,b))
fn(hyp(n,a,b),r(add(n,_4()),a,b))

fn(dec(a),tsb(a,_1()))
fn(not(a),tsb(_1(),a))
fn(isZero(a),not(a))
fn(isNonZero(a),not(isZero(a)))
fn(If(a,b,c),add(mul(isNonZero(a),b),mul(isZero(a),c)))
fn(or(a,b),isNonZero(add(a,b)))
fn(and(a,b),isNonZero(mul(a,b)))
fn(eq(a,b),isZero(add(tsb(a,b),tsb(b,a))))
fn(lte(a,b),isZero(tsb(a,b)))
fn(lt(a,b),and(lte(a,b),not(eq(a,b))))
fn(gt(a,b),not(lte(a,b)))
fn(gte(a,b),not(lt(a,b)))
fn(min(a,b),if(lt(a,b),a,b))
fn(max(a,b),if(lt(a,b),b,a))
fn(rem(a,b),tsb(a,mul(b,div(a,b))))
fn(isDivisible(a,b),isZero(rem(a,b)))
fn(isEven(a),isDivisible(a,_2()))
fn(isOdd(a),not(isEven(a)))
fn(mag(a),div(a,a))
fn(ack(m,n),if(m,tsb(hyp(m,_2(),add(n,_3())),_3()),inc(n)))

fn(_root_mid(l,h),div(inc(add(l,h)),_2()))
fn(_root(n,a,b,l,h),if(gte(l,h),l,if(lte(pow(_root_mid(l,h),b),a),r(_1(),dec(n),a,b,_root_mid(l,h),h),r(_1(),dec(n),a,b,l,dec(_root_mid(l,h))))))
fn(root(a,b),_root(a,a,b,_0(),a))

fn(_mytsb(b,a),if(b,dec(r(_1(),dec(b),a)),a))
fn(mytsb(a,b),_mytsb(b,a))

fn(_mydiv(b,n,d,q),if(lt(b,d),q,r(_1(),tsb(b,d),n,d,inc(q))))
fn(mydiv(a,b),_mydiv(a,a,b,_0()))

fn(_mypow(b,a),if(eq(b,_0()),_1(),if(eq(b,_1()),a,mul(a,r(_1(),dec(b),a)))))
fn(mypow(a,b),_mypow(b,a))

fn(_isPrime(i,n),if(lt(i,_2()),_1(),if(isDivisible(n,i),_0(),r(_1(),dec(i),n))))
fn(isPrime(n),if(n,_isPrime(dec(n),n),_0()))

fn(gcd(a,b),if(b,r(_1(),b,rem(a,b)),a))

fn(_nthPrime(b,i,n),if(n,if(isPrime(i),r(_1(),dec(b),inc(i),dec(n)),r(_1(),dec(b),inc(i),n)),dec(i)))
fn(nthPrime(n),_nthPrime(mul(n,n),_2(),n))

fn(f(a),r(_1(),tsb(a,_1())))

fn(main(a,b),pow(a,b))
