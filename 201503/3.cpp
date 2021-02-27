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
    int a, b, c, y1, y2;
    cin >> a >> b >> c >> y1 >> y2;

    int days = 0;
    for (int y = 1850; y <= y2; y ++ ) {
        for (int m = 1; m <= 12; m ++ ) {
            if (y >= y1 && m == a) {
                bool flag = true;
                int w = (1 + days) % 7;
                for (int i = 1, j = 0; i <= get_month(y, m); i ++ ) {
                    if (w == c - 1) {
                        if ( ++ j == b) {
                            printf("%04d/%02d/%02d\n", y, m, i);
                            flag = false;
                            break;
                        }
                    }
                    w = (w + 1) % 7;
                }
                if (flag) puts("none");
            }
            days += get_month(y, m);
        }
    }
    return 0;
}