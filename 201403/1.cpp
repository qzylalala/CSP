#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;

int n;
int s[N];

int main() {
    cin >> n;
    while (n -- ) {
        int x;
        cin >> x;
        s[abs(x)] ++ ;
    }

    int res = 0;
    for (int i = 1; i <= 1000; i ++ )
        if (s[i] > 1)
            res ++ ;
    cout << res << endl;
    return 0;
}