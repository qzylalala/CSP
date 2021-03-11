#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    int res = 0, x, score = 0;
    while (cin >> x, x) {
        if (x == 1) res ++, score = 0;
        else score += 2, res += score;
    }
    cout << res << endl;
    return 0;
}