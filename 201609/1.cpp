#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int a[1010];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    int diff = 0;
    for (int i = 1; i < n; i++) diff = max(abs(a[i] - a[i - 1]), diff);

    cout << diff << endl;

    return 0;
}