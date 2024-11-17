def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def prime_factors_sum(n):
    prime_sum = 0
    i = 2
    while i * i <= n:
        while n % i == 0:
            prime_sum += sum(map(int, str(i)))
            n //= i
        i += 1
    if n > 1:
        prime_sum += sum(map(int, str(n)))
    return prime_sum

def find_smith_number(n):
    n += 1
    while True:
        if not is_prime(n) and prime_factors_sum(n) == sum(map(int, str(n))):
            return n
        n += 1

while True:
    n = int(input())
    if n == 0:
        break
    smith_number = find_smith_number(n)
    print(smith_number)
