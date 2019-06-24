/*
    三次样条插值
 */
#include <iostream>
#include <vector>
#include <cmath>
const int maxn = 110;
using namespace std;
vector<double> x, y, xx;
double ys, ye;
int n, m;
vector<double> M;
void print(vector<double> tmp)
{
    for (auto x : tmp)
        cout << x << "\n";
    cout << "\n";
}
void catchToSolve(vector<double> a, vector<double> b, vector<double> c, vector<double> y)
{
    double x[maxn], l[maxn], u[maxn];
    l[0] = b[0];
    for (int i = 0; i < n - 1; i++)
    {
        u[i] = c[i] / l[i];
        l[i + 1] = b[i + 1] - a[i + 1] * u[i];
    }
    y[0] /= l[0];
    for (int i = 1; i < n; i++)
        y[i] = (y[i] - a[i] * y[i - 1]) / l[i];
    x[n - 1] = y[n - 1];
    for (int i = n - 2; i > -1; i--)
        x[i] = y[i] - u[i] * x[i + 1];
    for (int i = 0; i < n; i++)
        M.emplace_back(x[i]);
}
vector<string> cubicSpline(vector<double> x, vector<double> y, double ys, double ye, vector<double> xx)
{
    vector<double> a, b, c, d, h;
    vector<string> ans;
    for (int i = 0; i < x.size() - 1; i++)
        h.emplace_back(x[i + 1] - x[i]);
    for (int i = 0; i < x.size(); i++)
        b.emplace_back(2);
    a.emplace_back(0), c.emplace_back(1);
    for (int i = 0; i < h.size() - 1; i++)
        a.emplace_back(h[i] / (h[i] + h[i + 1])), c.emplace_back(1 - a[i + 1]);
    a.emplace_back(1);
    double d0 = (6 / h[0]) * ((y[1] - y[0]) / h[0] - ys);
    double dl = (6 / h.back()) * (ye - (y[y.size() - 1] - y[y.size() - 2]) / h.back());
    d.emplace_back(d0);
    for (int i = 0; i < h.size() - 1; i++)
        d.emplace_back((6 / (h[i] + h[i + 1])) * ((y[i + 2] - y[i + 1]) / h[i + 1] - (y[i + 1] - y[i]) / h[i]));
    d.emplace_back(dl);
    if (M.empty())
        catchToSolve(a, b, c, d);
    for (int j = 0; j < xx.size(); j++)
        for (int i = 0; i < x.size() - 1; i++)
            if (x[i] <= xx[j] && x[i + 1] >= xx[j])
            {
                double temp = pow((x[i + 1] - xx[j]), 3) / (6 * h[i]) * M[i] + pow(xx[j] - x[i], 3) / (6 * h[i]) * M[i + 1] + (x[i + 1] - xx[j]) / h[i] * (y[i] - h[i] * h[i] / 6 * M[i]);
                temp += (xx[j] - x[i]) / h[i] * (y[i + 1] - h[i] * h[i] / 6 * M[i + 1]);
                string cur = to_string(temp);
                ans.emplace_back(cur);
                break;
            }
    return ans;
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        double xx, yy;
        cin >> xx >> yy;
        x.emplace_back(xx), y.emplace_back(yy);
    }
    cin >> ys >> ye;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        double t;
        cin >> t;
        xx.emplace_back(t);
    }
    vector<string> ans = cubicSpline(x, y, ys, ye, xx);
    for (auto x : ans)
        cout << x << "\n";
    return 0;
}
/*
4
-1 0
0 0.5
1 2
2 1.5
0.5 -0.5
2
0.5
1.5
 */