#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int dp[40];

int main() {
    cin >> n;
    dp[0] = 0, dp[1] = 1, dp[2] = 2, dp[3] = 4, dp[4] = 5, dp[5] = 7;
    for (int i = 6; i <= 30; i++) {
        dp[i] = max(dp[i - 1] + 1, max(dp[i - 3] + 4, dp[i - 5] + 7));
    } 

    cout << dp[n / 10] << endl;

    return 0;
}