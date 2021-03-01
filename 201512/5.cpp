// cv   bitset  快速幂  (不开优化只有70分)

#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse-lm")

#include <iostream>
#include <cstdio>
#include <bitset>
#include <cstring>
#define rint register int
using namespace std;

typedef unsigned int U;

const int N = 1000, W = 32;


inline int cb(U x){  
    x = x ^ (x >> 1);
    x = x ^ (x >> 2);
    x = x ^ (x >> 4);
    x = x ^ (x >> 8);
    x = x ^ (x >> 16);
    return x;
}

struct Bit{
    U a[32];
    void inline set1(int x) {
        a[x >> 5] |= 1ull << (x & 31);
    }
    void inline set0(int x) {
        a[x >> 5] &= ~(1ull << (x & 31));
    }
    int inline get(int x) {
        return a[x >> 5] >> (x & 31) & 1;
    }
    void inline clear() {
        memset(a, 0, sizeof a);
    }
    Bit operator & (const Bit &b) const {
        Bit c;
        for (rint i = 0; i < 32; i++)
            c.a[i] = a[i] & b.a[i];
        return c;
    }
    bool inline count() {
        int res = 0;
        for (rint i = 0; i < 32; i++)
            res ^= cb(a[i]);
        return res & 1;
    }   
};

struct Mat{
    Bit w[N], bw[N];
    int n, m;
    Mat inline operator * (const Mat &b) const {
        Mat c; c.n = n, c.m = b.m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < c.m; j++) {
                if ((w[i] & b.bw[j]).count()) 
                    c.w[i].set1(j), c.bw[j].set1(i);
                else c.w[i].set0(j), c.bw[j].set0(i);
            }
        }
        return c;
    }
} s, A[30];

int m;

char str[N + 5];

int main() {
    scanf("%d", &m);
    A[0].n = A[0].m = m, s.n = 1, s.m = m;
    for (int i = 0; i < m; i++) {
        scanf("%s", str);
        for (int j = 0; j < m; j++) {
            if (str[j] == '1') A[0].w[j].set1(i), A[0].bw[i].set1(j);
        }
    }
    scanf("%s", str);
    for (int i = 0; i < m; i++) {
        if (str[i] == '1') s.w[0].set1(i), s.bw[i].set1(0);
    }
    for (int i = 1; i < 30; i++) A[i] = A[i - 1] * A[i - 1];
    int n; scanf("%d", &n);
    while (n--) {
        int b; scanf("%d", &b);
        Mat res = s;
        for (int i = 0; i < 30; i++) {
            if (b >> i & 1) res = res * A[i]; 
        }
        for (int i = 0; i < m; i++) putchar(res.w[0].get(i) ? '1' : '0');
        puts("");
    }
}