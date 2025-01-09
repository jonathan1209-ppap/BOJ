from decimal import getcontext,Decimal,ROUND_HALF_UP
getcontext().prec=50
getcontext().rounding=ROUND_HALF_UP
PI=Decimal('3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196')
a,b,c=map(Decimal,input().split())
def sin(x):
    x=x%(2*PI)
    getcontext().prec+=2
    i,lasts,s,fact,num,sign=1,0,x,1,x,1
    while s!=lasts:
        lasts=s
        i+=2
        fact*=i*(i-1)
        num*=x*x
        sign*=-1
        s+=num/fact*sign
    getcontext().prec-=2
    return +s
l,r=(c-b)/a,(c+b)/a
while r-l>Decimal(10**-25):
    mid=(l+r)/2
    if a*mid+b*sin(mid)<c:
        l=mid
    else:
        r=mid
print(round(r,6))
