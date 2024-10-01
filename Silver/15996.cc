#include <iostream>
#include <algorithm>
#include <vector> 
using namespace std;

long long int func(long long int n,long long int p){
    long long int mk=0;
    while (n>=p){
        mk += n/p;
        n/=p;
    }
    return mk;
}

int main() 
{
  ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  long long int n,m;
  cin>>n>>m;

    cout << func(n,m);
}
