#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

vector<string> strs;

int work_link(string str, int i) {
    string text, link;
    for (i ++; str[i] != ']'; i ++ ) {
        char c = str[i];
        if (c == '_') {
            text += "<em>";
            i ++ ;
            while (str[i] != '_') text += str[i ++ ];
            text += "</em>";
        }
        else text += c;
    }

    for (i += 2; str[i] != ')'; i ++ )
        link += str[i];
    printf("<a href=\"%s\">%s</a>", link.c_str(), text.c_str());
    return i;
}

int work_em(string str, int i) {
    printf("<em>");
    for (i ++; str[i] != '_'; i ++ ) {
        char c = str[i];
        if (c == '[') i = work_link(str, i);
        else cout << c;
    }
    printf("</em>");
    return i;
}

void work_line(string str) {
    int k = 0;
    while (str[k] == ' ') k ++ ;
    str = str.substr(k);

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '_') {
            i = work_em(str, i);
        }
        else if (str[i] == '[') {
            i = work_link(str, i);
        }
        else {
            cout << str[i];
        }
    }
}

void work(int a, int b) {
    if (strs[a][0] == '#') {
        int cnt = 0;
        while(strs[a][cnt] == '#') cnt ++;

        printf("<h%d>", cnt);
        work_line(strs[a].substr(cnt));
        printf("</h%d>\n", cnt);
    }
    else if (strs[a][0] == '*') {
        printf("<ul>\n");
        for (int i = a; i <= b; i++) {
            printf("<li>");
            work_line(strs[i].substr(1));
            printf("</li>\n");
        }
        printf("</ul>\n");
    }
    else {
        printf("<p>");
        for (int i = a; i <= b; i++) {
            work_line(strs[i]);
            if (i != b) cout << endl;
        }
        printf("</p>\n");
    }
}

int main() {
    string str;
    while(getline(cin, str)) strs.push_back(str);

    for (int i = 0; i < strs.size(); i++) {
        if (strs[i].empty()) continue;

        int j = i;
        while(j < strs.size() && strs[j].size()) j ++;
        work(i, j - 1);
        i = j - 1;
    }

    return 0;
}