#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;

int n;
int b[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; i ++ ) cin >> b[i];

    int maxs = 0, mins = 0;
    for (int i = 0; i < n; i ++ ) {
        maxs += b[i];
        if (!i || b[i] > b[i - 1])
            mins += b[i];
    }

    cout << maxs << endl;
    cout << mins << endl;

    return 0;
}