mod = 1000000007

def pow(a, p):
    r = 1
    while p:
        if p & 1: r = r * a % mod
        a = a * a % mod
        p //= 2
    return r

def inv(a):
    return pow(a, mod - 2)

T = int(input())
for _ in range(T):
    r, g, b, k = map(int, input().split())
    ans = (r + k + k * g % mod * inv(b)) % mod
    ans = (ans + mod - r * pow(b * inv(b + 1) % mod, k) % mod) % mod
    print(ans)
