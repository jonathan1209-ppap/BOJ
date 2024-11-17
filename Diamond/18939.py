for i in range(int(input())):
    n,m,k=map(int,input().split())
    if max(n,m)<2*k:print("Yuto")
    else:
        if (n*m%2==0):print("Platina")
        else:print("Yuto")
