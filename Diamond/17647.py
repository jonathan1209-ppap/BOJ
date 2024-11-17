n,p=map(int,input().split())
r=1
if n<=p//2:
 for i in range(1,n+1):r=(r*i)%p
 print(r)
else:
 for i in range(n+1,p):r=(r*i)%p
 print(pow(-r,-1,p))
