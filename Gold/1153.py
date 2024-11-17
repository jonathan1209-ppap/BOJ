def s(n):
    primes = [True] * (n + 1)
    primes[0] = primes[1] = False
    p = 2
    while p * p <= n:
        if primes[p]:
            for i in range(p * p, n + 1, p):
                primes[i] = False
        p += 1
    return [i for i in range(2, n + 1) if primes[i]]

def f(n, primes,memo):
    if n in memo:
        return memo[n]
    for p1 in primes:
        for p2 in primes:
            for p3 in primes:
                p4 = n - p1 - p2 - p3
                if p4 in primes:
                    memo[n] = [p1, p2, p3, p4]
                    return memo[n]
    return None

N = int(input())
primes = s(N)
memo = {}
result = f(N, primes , memo)
if result:
    print(*result) 
else:
    print(-1)
