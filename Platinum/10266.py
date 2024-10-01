def make_table(sub):
    j=0
    table=[0]*(len(sub))
    for i in range(1,len(sub)):
        while j>0 and sub[i]!=sub[j]:
            j=table[j-1]
        if sub[i]==sub[j]:
            j+=1
            table[i]=j
    return table
def kmp(s,sub):
    table=make_table(sub)
    j=0
    for i in range(len(s)):
        while j>0 and s[i]!=sub[j]:
            j=table[j-1]
        if s[i]==sub[j]:
            if j==len(sub)-1:
                return True
            else:
                j+=1
    return False
a=int(input())
l1=list(map(int,input().split()))
l2=list(map(int,input().split()))
x1=[0]*360000
x2=[0]*360000
for x in l1:x1[x]=1
for x in l2:x2[x]=1
x1=x1+x1 
if kmp(x1,x2):print("possible")
else:print("impossible")
