#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> >Vec;
vector<bool>is_visited;

void DFS(int v){
    is_visited[v] = 1;
    for(auto i :Vec[v]){
        if(is_visited[i]) continue;
        DFS(i);
    }
}
int main()
{
    int n,m;
    int cnt = 0;

    cin >> n;
    cin >> m;
    Vec.resize(n+1);
    is_visited.resize(n+1);
    for (int i = 0; i < m; i++) {
        int a,b;

        cin >> a >> b;

        Vec[a].push_back(b);
        Vec[b].push_back(a);
    }
    DFS(1);

    for(auto i :is_visited){
        cnt += i;
    }

    cout << cnt-1;
    return 0;
}
