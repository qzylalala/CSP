#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

bool check(string str) {
    stack<char> st1;
    stack<int> st2;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= '0' && str[i] <= '9') st2.push(str[i] - '0');
        else if (str[i] == '+' || str[i] == '-') st1.push(str[i]);
        else {
            if (str[i] == 'x') {
                int pre = st2.top();
                st2.pop();
                int nxt = str[i + 1] - '0';
                st2.push(pre * nxt);
            }
            else {
                int pre = st2.top();
                st2.pop();
                int nxt = str[i + 1] - '0';
                st2.push(pre / nxt);
            }
            i ++;
        }
    }

    stack<char> stk1;
    stack<int> stk2;

    while(st1.size()) {
        stk1.push(st1.top());
        st1.pop();
    }

    while(st2.size()) {
        stk2.push(st2.top());
        st2.pop();
    }

    while(stk1.size()) {
        char ch = stk1.top();
        stk1.pop();

        int pre = stk2.top();
        stk2.pop();
        int nxt = stk2.top();
        stk2.pop();

        if (ch == '+') {
            stk2.push(pre + nxt);
        }
        else {
            stk2.push(pre - nxt);
        }
    }

    if (stk2.top() == 24) return true;
    else return false;
}

int main() {
    int n;
    cin >> n;

    while(n --) {
        string str;
        cin >> str;
        if (check(str)) puts("Yes");
        else puts("No");
    }

    return 0;
}