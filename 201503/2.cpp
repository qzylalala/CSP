#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
const int N = 1010;
pii p[N];
int n;

bool cmp(pii p1, pii p2) {
    if (p1.first > p2.first) return true;
    else if (p1.first < p2.first) return false;
    else {
        if (p1.second < p2.second) return true;
        else return false;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        p[x].first ++;
        p[x].second = x;
    }

    sort(p, p + N, cmp);

    for (int i = 0; i < n; i++) {
        if (p[i].first != 0)
            cout << p[i].second << " " << p[i].first << endl;
    }

    return 0;
}