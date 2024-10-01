def make_table(sub):
    j=0
    for i in range(1,len(sub)):
        while j>0 and sub[i]!=sub[j]:
            j=table[j-1]
        if sub[i]==sub[j]:
            j+=1
            table[i]=j
a=int(input())
b=input()
table=[0 for i in range(a)]
make_table(b)
print(a-table[a-1])
