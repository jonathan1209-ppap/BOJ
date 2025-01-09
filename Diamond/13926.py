from random import randrange
from math import gcd

class Factorize:
    def _f(self, x: int, a: int, n: int) -> int:
        return (pow(x, 2) + a) % n

    def __pollard_rho(self, n: int) -> int:
        x = randrange(1, n)
        c = randrange(1, n)
        y, g = x, 1

        while g == 1:
            x = self._f(x, c, n)
            y = self._f(self._f(y, c, n), c, n)
            g = gcd(abs(x - y), n)
        if g == n:
            return self.__pollard_rho(n)
        return g

    def factorize(self, n: int) -> list[int]:
        if n == 1:
            return []
        if ~n & 1:
            return [2] + self.factorize(n >> 1)
        if Primetest().process(n):
            return [n]
        f = self.__pollard_rho(n)
        return self.factorize(f) + self.factorize(n // f)


class Primetest:
    def __verify(self, a: int, n: int, s: int) -> bool:
        if a >= n:
            a %= n
        if a < 2:
            return True
        d = n >> s
        x = pow(a, d, n)
        if x == n - 1 or x == 1:
            return True
        for _ in range(s):
            x = pow(x, 2, n)
            if x == 1:
                return False
            if x == n - 1:
                return True
        return False

    def process(self, n: int) -> bool:
        if n == 2:
            return True
        if n < 2 or ~n & 1:
            return False
        r, d = 1, n >> 1
        while ~d & 1:
            d >>= 1
            r += 1
        return all(self.__verify(i, n, r) for i in ([2, 7, 61] if n < 4759123141 else [2, 325, 9375, 28178, 450775, 9780504, 1795265022]))

n = int(input().strip())
factorizer = Factorize()
factors = list(set(factorizer.factorize(n)))
res=0
for i in range(1,1<<len(factors)):
  tmp=1
  for j in range(len(factors)):
    if i&(1<<j):tmp*=factors[j]
  res+=(1 if bin(i)[2:].count('1')&1 else -1)*n//tmp
print(n-res)
