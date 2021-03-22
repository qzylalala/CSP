#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;

int main() {
    cin >> n;

    int sum = 0;

    for (int i = 1; i <= n; i++) {
        int w, score;
        cin >> w >> score;

        sum += w * score;
    }

    if (sum > 0) cout << sum << endl;
    else cout << "0" << endl;

    return 0;
}