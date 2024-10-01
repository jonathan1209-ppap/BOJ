#include <iostream>
#include <algorithm>
#include <vector> 
using namespace std;

int a[500002];int c;

int main() 
{
  ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  int n,m;
  cin>>n;
  for (int i=0;i<n;i++){
    cin>>c;
    a[i]=c;
  }
  
  sort(a,a+n);
  
  cin>>m;
  for(int i=0;i<m;i++){
    cin>>c;
    cout<<upper_bound(a,a+n,c)-lower_bound(a,a+n,c)<<" ";
  }
}
