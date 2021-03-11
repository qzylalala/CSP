#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;

int n, L, T;
struct Ball
{
    int p, v;
}b[N];

int main()
{
    cin >> n >> L >> T;
    for (int i = 0; i < n; i ++ )
    {
        cin >> b[i].p;
        b[i].v = 1;
    }
    while (T -- )
    {
        for (int i = 0; i < n; i ++ )
        {
            b[i].p += b[i].v;
            if (b[i].p == L || !b[i].p)
                b[i].v *= -1;
        }
        for (int i = 0; i < n; i ++ )
            for (int j = i + 1; j < n; j ++ )
                if (b[i].p == b[j].p)
                {
                    b[i].v *= -1;
                    b[j].v *= -1;
                }
    }
    for (int i = 0; i < n; i ++ )
        cout << b[i].p << ' ';
    return 0;
}