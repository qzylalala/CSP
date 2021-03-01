#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;

int main() {
    cin >> n;

    int sum = 0;
    while(n) {
        sum += n % 10;
        n /= 10;
    }

    cout << sum << endl;

    return 0;
}