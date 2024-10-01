#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define endl "\n"

int dp[49];

int main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int T;
    dp[0]=1;
    dp[1]=1;
    for (int i=2;i<=49;i++){
        dp[i]=dp[i-1]+dp[i-2];
    }

    cin >> T;
    while (T--){
        int n;
        cin >> n;
        cout << dp[n] << endl;

    }
}
