#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

vector<vector<int> >Vec;
vector<bool>is_visited;
vector<int> dist;


void DFS(int v){
    is_visited[v] = 1;
    
    for(auto i :Vec[v]){
        if(is_visited[i]) continue;
        dist[i]=dist[v]+1;
        DFS(i);
    }
}

int main()
{
    int n,a,b;

    cin >> n;
    
    int m;
    cin >> a >> b;
    cin >> m;
    
    Vec.resize(n+1);
    is_visited.resize(n+1);
    dist.resize(n+1);
    
    for (int i=1; i<=m; i++){
        int x,y;
        cin >> x >> y;
        
        Vec[y].push_back(x);
        Vec[x].push_back(y);
    }
    
    DFS(a);
    if (dist[b]==0){cout << -1 << "\n"; return 0;}
    cout << dist[b] << "\n"; 
    
    return 0;
}
