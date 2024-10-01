#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

#define endl "\n"

stack<int> stk;

int main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int T;


    cin >> T;
    while (T--){
        int cmd;
        cin >> cmd;

        if (cmd==1){
            int x;
            cin >>x;
            stk.push(x);
        } else if (cmd==2) {
            if (stk.empty()) {
                cout << -1 << endl;
            } else {
                cout << stk.top() << endl;
                stk.pop();
            }
        } else if (cmd==3) {
            cout << stk.size() << endl;
        } else if (cmd==4) {
            if (stk.empty()) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        } else {
            if (stk.empty()) {
                cout << -1 << endl;
            } else {
                cout << stk.top() << endl;
            }
        }

    }
}
