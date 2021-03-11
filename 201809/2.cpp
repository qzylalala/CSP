#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

const int N = 2010;
int n;
pii a[N], b[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int st, end;
        cin >> st >> end;
        a[i] = {st, end};
    }

    for (int i = 0; i < n; i++) {
        int st, end;
        cin >> st >> end;
        b[i] = {st, end};
    }

    int i = 0, j = 0;
    int sum = 0;
    while(i < n && j < n) {
        if (a[i].y <= b[j].x) i ++;
        else if (a[i].x >= b[j].y) j ++;
        else {
            if (a[i].y <= b[j].y) {
                if (a[i].x >= b[j].x) sum += (a[i].y - a[i].x);
                else sum += (a[i].y - b[j].x);
                i ++;
            }
            else {
                if (a[i].x <= b[j].x) sum += (b[j].y - b[j].x);
                else sum += (b[j].y - a[i].x);
                j ++;
            }
        }
    }

    cout << sum << endl;

    return 0;
}