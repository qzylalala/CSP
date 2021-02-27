#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;
int cnt[N];
int n;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x] ++;
        cout << cnt[x] << " ";
    }

    cout << endl;

    return 0;
}