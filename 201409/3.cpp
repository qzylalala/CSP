#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;

string Lower(string s) {
    string res;
    for (int i = 0; i < s.size(); i ++ )
        res += tolower(s[i]);
    return res;
}

int main() {
    string S;
    cin >> S;
    int type;
    cin >> type;

    int n;
    cin >> n;
    while (n -- ) {
        string line;
        cin >> line;
        if (type && line.find(S) != -1) cout << line << endl;
        else if (!type && Lower(line).find(Lower(S)) != -1) cout << line << endl;
    }

    return 0;
}