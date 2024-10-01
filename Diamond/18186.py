ans=0
c=cc=0

n,b,q=map(int,input().split())

l=list(map(int,input().split()))
l.append(0)
l.append(0)
for i in range(n):
    if (b>q):
        if l[i+1]>l[i+2]:
            c = min(l[i],l[i+1]-l[i+2])
            l[i] -= c
            l[i+1]-=c
            ans += c*(b+q)
            cc = min({l[i] , l[i+1] , l[i+2]})
            l[i] -= cc
            l[i+1]-=cc
            l[i+2]-=cc
            ans += cc*(b+2*q)
        else:
            cc = min({l[i] , l[i+1] , l[i+2]})
            l[i] -= cc
            l[i+1]-=cc
            l[i+2]-=cc
            ans += cc*(b+2*q)
    ans += l[i]*b
print(ans)
