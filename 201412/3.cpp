#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

typedef pair<double, int> pdi;

const int N = 5010;
pdi buy[N], sell[N];
int tot, b, s;
int buy_num, sell_num;
map<int, int> mp;   // 总记录  ->  buy 和 sell (+ : buy  - : sell)
long long pre1[N], pre2[N];
double ps[N * 2];

int main() {
    string op;
    double price;
    int num;

    for (int i = 0; i < N; i++) {
        buy[i] = {10000.0, 0};
        sell[i] = {10000.0, 0};
    }
    while(cin >> op) {
        tot ++;
        if (op == "buy") {
            cin >> price >> num;
            b ++;
            buy_num ++;
            buy[b] = {price, num};
            mp[tot] = b;
        }
        else if (op == "sell") {
            cin >> price >> num;
            s ++;
            sell_num ++;
            sell[s] = {price, num}; 
            mp[tot] = -1 * s;
        }
        else {
            int idx;
            cin >> idx;
            int row = mp[idx];
            if (row > 0) buy[row] = {10000.0, 0}, buy_num --;
            else sell[-1 * row] = {10000.0, 0}, sell_num --;
        }
    }

    sort(buy + 1, buy + b + 1);
    sort(sell + 1, sell + s + 1);

    for (int i = 1; i <= buy_num; i++) {
        ps[i] = buy[i].first;
        pre1[i] = pre1[i - 1] + buy[i].second;
    } 


    for (int i = 1; i <= sell_num; i ++) {
        ps[i + buy_num] = sell[i].first;
        pre2[i] = pre2[i - 1] + sell[i].second;
    }

    sort(ps + 1, ps + buy_num + sell_num + 1);

    double p0;
    long long ans = 0;

    int l = 1, r = 1;
    for (int i = 1; i <= buy_num + sell_num; i ++) {
        double p = ps[i];
        while(l <= buy_num && buy[l].first < p) l ++;
        while(r <= sell_num && sell[r].first <= p) r ++;

        long long tmp = min(pre1[buy_num] - pre1[l - 1], pre2[r - 1] - pre2[0]);
        // cout << ps[i] << " " << l << " " << r << " " << tmp << endl;
        if (tmp >= ans) {
            ans = tmp;
            p0 = p;
        }
    }

    printf("%.2f %lld\n", p0, ans);

    return 0;
}