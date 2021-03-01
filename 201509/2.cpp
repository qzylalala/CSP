#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int month[] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

// 判断 是否为 闰年
int is_leap(int year) {
    if (year % 4 == 0 && year % 100 || year % 400 == 0)
        return 1;
    return 0;
}

// 获取 m 月 天数
int get_month(int y, int m) {
    if (m == 2) return month[m] + is_leap(y);
    return month[m];
}

int main() {
    int year, day;
    cin >> year >> day;

    int mon = 0, da = 0;
    for (int i = 1; i <= 12; i++) {
        int d = get_month(year, i);
        if (d >= day) {
            mon = i;
            da = day;
            break;
        } 
        else day -= d;
    }

    cout << mon << endl;
    cout << da << endl;

    return 0;
}