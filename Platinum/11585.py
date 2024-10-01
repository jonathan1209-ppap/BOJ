def gcd(a,b):
 while b>0:
  r=a%b
  a=b
  b=r
 return a
def make_table(pattern):
 table=[0 for _ in range(len(pattern))]
 j=0
 for i in range(1,len(pattern)):
  while j>0 and pattern[i]!=pattern[j]:
   j=table[j-1]
  if pattern[i]==pattern[j]:
   j+=1
   table[i]=j
 return table
def kmp(parent,pattern):
 table=make_table(pattern)
 cnt=0
 j=0
 for i in range(len(parent)-1):
  while j>0 and parent[i]!=pattern[j]:
   j=table[j-1]
  if parent[i]==pattern[j]:
   if len(pattern)-1==j:
    cnt+=1
    j=table[j]
   else:
    j+=1
 return cnt
asdfasdf=int(input())
a=input().replace(" ","")
b=input().replace(" ","")
x=len(a)
y=kmp(a+a,b)
g=gcd(x,y)
print(f"{(y//g)}/{(x//g)}")
