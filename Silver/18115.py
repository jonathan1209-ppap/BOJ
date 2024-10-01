import collections
a=int(input())
l=list(map(int,input().split()))
l=l[::-1]
deq=collections.deque()
for i in range(a):
    if l[i]==1:
        deq.appendleft(i+1)
    elif l[i]==2:
        deq.insert(1,i+1)
    elif l[i]==3:
        deq.append(i+1)
for i in deq:
    print(i,end=" ")
