a=int(input())
dp=[0]*(10009)
dp[0]=0
dp[1]=1
dp[2]=2
for i in range(3,a+1):
    dp[i]=(dp[i-1]+dp[i-2])%10007
print(dp[a]%10007)
