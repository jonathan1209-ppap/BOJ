a=int(input())
res=0
for i in range(1,a+1):
    si=str(i)
    x=0
    if i<100:
        res+=1
    else:
        if int(si[0])-int(si[1]) == int(si[1])-int(si[2]):
            res+=1
print(res)
