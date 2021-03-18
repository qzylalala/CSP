#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 110, M = 2010;

int n, m;
double R;
double o[N], p[M][N];
double d[M], rd[M];
double ans[M];

inline double sqr(double x)
{
    return x * x;
}

int main()
{
    scanf("%d%d%lf", &n, &m, &R);
    for (int i = 0; i < n; i ++ ) scanf("%lf", &o[i]);
    for (int i = 0; i < m; i ++ )
    {
        double s = 0;
        for (int j = 0; j < n; j ++ )
        {
            scanf("%lf", &p[i][j]);
            s += sqr(p[i][j] - o[j]);
        }
        d[i] = sqrt(s);
        rd[i] = sqrt(s - sqr(R));
    }

    for (int i = 0; i < m; i ++ )
        for (int j = 0; j < i; j ++ )
        {
            double s = 0;
            for (int k = 0; k < n; k ++ ) s += sqr(p[i][k] - p[j][k]);
            double c = sqrt(s), a = d[i], b = d[j];
            double p = (a + b + c) / 2;
            double area = sqrt(p * (p - a) * (p - b) * (p - c));
            double h = area * 2 / c;
            if (h >= R || sqr(b) >= sqr(a) + s || sqr(a) >= sqr(b) + s)
            {
                ans[i] += c, ans[j] += c;
                continue;
            }
            double angle1 = acos((sqr(a) + sqr(b) - s) / (2 * a * b));
            double angle2 = acos(R / a);
            double angle3 = acos(R / b);
            double t = (angle1 - angle2 - angle3) * R + rd[i] + rd[j];
            ans[i] += t, ans[j] += t;
        }
    for (int i = 0; i < m; i ++ )
        printf("%.12lf\n", ans[i]);
    return 0;
}