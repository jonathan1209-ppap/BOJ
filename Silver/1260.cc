#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

vector<vector<int> >Vec;
vector<bool>is_visited1;
vector<bool>is_visited2;
queue<int>que;


void DFS(int v){
    is_visited1[v] = 1;
    cout << v <<" ";
    for(auto i :Vec[v]){
        if(is_visited1[i]) continue;
        DFS(i);
    }
}

void BFS(int x){
    is_visited2[x] = 1;
    que.push(x);
    while (!que.empty()){
        int px=que.front();
        cout << px << " ";
        que.pop();
        for(auto nx :Vec[px]){
            if(!is_visited2[nx]){
                is_visited2[nx]=1;
                que.push(nx);
            }
        }

    }
}

int main()
{
    int n,m,k;

    cin >> n;
    cin >> m;
    cin >> k;
    Vec.resize(n+1);
    is_visited1.resize(n+1);
    is_visited2.resize(n+1);
    for (int i = 0; i < m; i++) {
        int a,b;

        cin >> a >> b;

        Vec[a].push_back(b);
        Vec[b].push_back(a);
    }
    
    for (int i=1; i<=n; i++){
        sort(Vec[i].begin(), Vec[i].end());
    }

    DFS(k);cout<<"\n";
    BFS(k);cout<<"\n";
    return 0;
}
