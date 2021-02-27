#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    string s;//保存ISBN 号码
    cin >> s;

    int check = 0;//

    for(int i = 0, k = 1;k <= 9; i++){
        char x = s[i];
        if(x != '-')
            check += (x-'0') * k, k++;
    }

    check = check % 11;
    if((check == 10 && 'X' == s.back()) || check == s.back() - '0')//校验位正确
        cout << "Right" << endl;
    else {
        if(check == 10)
            cout << s.substr(0, 12) + 'X' << endl;
        else
            cout << s.substr(0, 12) << check << endl;
    }
    return 0;
}