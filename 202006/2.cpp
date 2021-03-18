#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef long long ll;
typedef pair<int, ll> pii;

const int N = 500010;
int n, a, b;
pii u[N], v[N];

int main() {
    cin >> n >> a >> b;

    for (int i = 1; i <= a; i++) {
        int idx;
        ll val;
        cin >> idx >> val;
        u[i] = {idx, val};
    }
    sort(u + 1, u + a + 1);

    for (int i = 1; i <= b; i++) {
        int idx;
        ll val;
        cin >> idx >> val;
        v[i] = {idx, val};
    }
    sort(v + 1, v + b + 1);

    ll sum = 0;
    int i = 1, j = 1;
    while(i <= a && j <= b) {
        if (u[i].x < v[j].x) {
            i ++;
        }
        else if (u[i].x == v[j].x) {
            sum += u[i].y * v[j].y;
            i ++;
            j ++;
        }
        else {
            j ++;
        }
    }

    cout << sum  << endl;
}