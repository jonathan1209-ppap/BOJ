#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

vector<vector<int> >Vec;
vector<bool>is_visited;
vector<int>ord;

int b;
int chk=1;
queue<int>que;

void BFS(int x){
    is_visited[x] = 1;
    que.push(x);
    while (!que.empty()){
        int px=que.front();
        ord[px]=chk++;
        que.pop();
        for(auto nx :Vec[px]){
            if(!is_visited[nx]){
                is_visited[nx]=1;
                que.push(nx);
            }
        }

    }
}

int main()
{
    int n,m,k;

    cin >> n >> m >> k;
    
    
    Vec.resize(n+1);
    is_visited.resize(n+1);
    ord.resize(n+1);
    
    for (int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        Vec[u].push_back(v);
        Vec[v].push_back(u);
    }
    
    for (int i=1;i<=n;i++){
        sort(Vec[i].begin(),Vec[i].end(),greater<int>());
    }
    
    BFS(k);
    for (int i=1;i<=n;i++){
        cout << ord[i] << "\n";
    }
    
    return 0;
}
