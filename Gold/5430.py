from collections import deque


def sol(n,arr):
    val=False
    l=deque()
    for x in arr:
        l.append(x)
    for op in n:
        if op=='R':val=not val
        elif op=='D':
            if not l:return"error"
            if val:l.pop()
            else:l.popleft()
    res=list(l)[::-1] if val else list(l)
    return'['+','.join(map(str,res))+']'

for i in range(int(input())):
    n=input().strip()
    a=int(input())
    arr=[]
    if a>0:arr=list(map(int,input().strip()[1:-1].split(','))) 
    else:
        input()
    print(sol(n,arr))

    """import sys 
input=sys.stdin.read"""
