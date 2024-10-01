U, N = map(int, input().split())
b, c = [], {}

for _ in range(N):
    n, p = input().split()
    p = int(p)
    b.append((n, p))
    c[p] = c.get(p, 0) + 1

mc = min(c.values())
wp = min(p for p in c if c[p] == mc)

for n, p in b:
    if p == wp:
        print(n, p)
        break
