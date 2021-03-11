#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;

const int N = 1010;
int n;
pii player[2][8];

int main() {
    cin >> n;
    int cnt = 0;
    player[0][0] = {0, 30};
    player[1][0] = {0, 30};

    while(n -- ) {
        string op;
        cin >> op;

        int idx = cnt % 2;
        if (op == "summon") {
            int pos, attack, health;
            cin >> pos >> attack >> health;
            for (int i = pos; i <= 7; i++) {
                int x = player[idx][i].x, y = player[idx][i].y;
                player[idx][i].x = attack, player[idx][i].y = health;
                attack = x, health = y;
            }
        }
        else if (op == "attack") {
            int pos1, pos2;
            cin >> pos1 >> pos2;
            int idx1 = idx, idx2 = 1 - idx;

            player[idx1][pos1].y -= player[idx2][pos2].x;
            player[idx2][pos2].y -= player[idx1][pos1].x;

            // check 生命值, 特判是否为 英雄
            if (player[idx1][pos1].y <= 0) {
                for (int i = pos1; i <= 6; i++) {
                    player[idx1][i] = player[idx1][i + 1];
                }
                player[idx1][7] = {0, 0};
            }

            if (player[idx2][pos2].y <= 0) {
                if (pos2 == 0) {
                    continue;
                }
                else {
                    for (int i = pos2; i <= 6; i++) {
                        player[idx2][i] = player[idx2][i + 1];
                    }
                    player[idx2][7] = {0, 0};
                }
            }
        }
        else {
            cnt ++;
        }
    }

    if (player[0][0].y > 0 && player[1][0].y > 0) cout << "0" << endl;
    if (player[0][0].y <= 0) cout << "-1" << endl;
    if (player[1][0].y <= 0) cout << "1" << endl;

    int num1 = 0, num2 = 0;
    for (int i = 1; i <= 7; i++) {
        if (player[0][i].y > 0) num1 ++;
        if (player[1][i].y > 0) num2 ++;
    }

    cout << player[0][0].y << endl;
    cout << num1;
    for (int i = 1; i <= num1; i++) cout << " " << player[0][i].y;
    cout << endl;

    cout << player[1][0].y << endl;
    cout << num2;
    for (int i = 1; i <= num2; i++) cout << " " << player[1][i].y;
    cout << endl;

    return 0;
}