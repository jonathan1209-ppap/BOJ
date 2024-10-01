def make_table(sub):
    j=0
    for i in range(1,len(sub)):
        while j>0 and sub[i]!=sub[j]:
            j=table[j-1]
        if sub[i]==sub[j]:
            j+=1
            table[i]=j
    return len(sub)-table[len(sub)-1]
while True:
    a=input()
    table=[0 for _ in range(len(a))]
    if a=='.':
        break
    if len(a)%make_table(a):
        print(1)
    else:
        print(len(a)//make_table(a))
