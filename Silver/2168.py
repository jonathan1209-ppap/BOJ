import math
def sol(x,y):return x+y-math.gcd(x,y)
print(sol(*[*map(int,input().strip().split())]))
