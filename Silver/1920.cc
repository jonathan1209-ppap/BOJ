#include <iostream>
#include <algorithm>
#include <vector> 
using namespace std;

vector<int> a;

int main() 
{
    ios::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);
  
  int n,m;
  
  cin >> n;
  for(int i=0;i<n;i++){
    int t;
    cin >> t;
    a.push_back(t);
  }
  sort(a.begin(),a.end());
  cin >> m;
  for(int i=0;i<m;i++){
    int x;
    cin >> x;
    cout << binary_search(a.begin(),a.end(),x) << "\n";
  }
}
