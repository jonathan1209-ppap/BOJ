def z(n, r, c):
    if n == 1:
        return r * 2 + c
    s = 2 ** (n - 1)
    if r < s and c < s:
        return z(n - 1, r, c)
    elif r < s and c >= s:
        return s * s + z(n - 1, r, c - s)
    elif r >= s and c < s:
        return 2 * s * s + z(n - 1, r - s, c)
    else:
        return 3 * s * s + z(n - 1, r - s, c - s)

N, r, c = map(int, input().split())
print(z(N, r, c))
