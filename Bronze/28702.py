a=input()
b=input()
c=input()
if a.isdigit():
    a=int(a)
    b=a+1
    c=a+2
    d=a+3
    if d%3==0 and d%5==0:
        print("FizzBuzz")
    elif d%3==0 and not d%5==0:
        print("Fizz")
    elif not d%3==0 and d%5==0:
        print("Buzz")
    else:
        print(d)
elif b.isdigit():
    b=int(b)
    a=b-1
    c=b+1
    d=b+2
    if d%3==0 and d%5==0:
        print("FizzBuzz")
    elif d%3==0 and not d%5==0:
        print("Fizz")
    elif not d%3==0 and d%5==0:
        print("Buzz")
    else:
        print(d)
elif c.isdigit():
    c=int(c)
    b=c-1
    a=c-2
    d=c+1
    if d%3==0 and d%5==0:
        print("FizzBuzz")
    elif d%3==0 and not d%5==0:
        print("Fizz")
    elif not d%3==0 and d%5==0:
        print("Buzz")
    else:
        print(d)
