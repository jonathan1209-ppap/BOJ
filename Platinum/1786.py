def make_table(sub):
    j=0
    for i in range(1,len(sub)):
        while j>0 and sub[i]!=sub[j]:
            j=table[j-1]
        if sub[i]==sub[j]:
            j+=1
            table[i]=j
def kmp(s,sub):
    make_table(sub)
    cnt=j=0
    for i in range(len(s)):
        while j>0 and s[i]!=sub[j]:
            j=table[j-1]
        if s[i]==sub[j]:
            if j==len(sub)-1:
               
                ans.append(i-len(sub)+2)
                cnt+=1
                j=table[j]
            else:
                j+=1
    return cnt
a=input()
b=input()
table=[0 for i in range(len(b))]
ans=[]
print(kmp(a,b))
print(*ans)
