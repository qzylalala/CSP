#include <iostream>

using namespace std;

const int N = 1010, M = 10010;
int n;
int a[N];
int cnt[M];

int main() {
    cin >> n;

    int ans = 0, max_cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]] ++;

        if (max_cnt < cnt[a[i]]) {
            ans = a[i];
            max_cnt = cnt[a[i]];
        }
        if (max_cnt == cnt[a[i]]) {
            ans = min(ans, a[i]);
        }
    }

    cout << ans << endl;
    return 0;
}