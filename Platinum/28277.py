import sys
input = sys.stdin.readline

def hapchigi(x:int,y:int,s:set,p):
    if len(s[p[x]]) > len(s[p[y]]):
        s[p[x]].extend(s[p[y]])
        s[p[y]] = []
    else:
        s[p[y]].extend(s[p[x]])
        s[p[x]] = []
        p[x], p[y] = p[y], p[x]

a,b=map(int,input().split())
s=[set(map(int, input().split()[1:])) for _ in range(a)]
for _ in range(b):
    cmd=[*map(int,input().split())]
    if cmd[0]==1:
        i=cmd[1]-1
        j=cmd[2]-1

        if len(s[i]) < len(s[j]):
            s[i], s[j] = s[j], s[i]
            
        s[i].update(s[j])
        s[j].clear()
    else:
        i=cmd[1]-1
        print(len(s[i]))
