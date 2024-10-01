def nth_palindrome(N):
    length = 1
    while True:
        count = 9 * 10**((length-1)//2)
        if N <= count:
            base = 10**((length-1)//2)
            num = base + N - 1
            num_str = str(num)
            if length % 2:
                return int(num_str + num_str[-2::-1])
            else:
                return int(num_str + num_str[::-1])
        N -= count
        length += 1

import sys
N = int(sys.stdin.readline().strip())
print(nth_palindrome(N))
