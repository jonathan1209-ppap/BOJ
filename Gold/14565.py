def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    gcd, x1, y1 = extended_gcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return gcd, x, y

def modular_inverse(a, n):
    gcd, x, y = extended_gcd(a, n)
    if gcd != 1:
        return None 
    return x % n

def find_inverse(n, a):
    add_inverse = (n - a) % n
    mul_inverse = modular_inverse(a, n)
    return add_inverse, mul_inverse

N, A = map(int, input().split())
add_inverse, mul_inverse = find_inverse(N, A)
if mul_inverse is None:
    print(add_inverse, -1)
else:
    print(add_inverse, mul_inverse)
