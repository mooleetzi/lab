/*
    列选主元解方程组
*/
#include <iostream>
#include<vector>
#include<cmath>
using namespace std;
using vd = vector<double>;
class Gauss
{
private:
    vector<vd> a;
    vd b;
    int n;
    void choose(int col)
    {
        double d = a[col][col];
        int c = col;
        for (int i = col + 1; i < n; i++)
            if (fabs(a[i][col]) > fabs(d))
            {
                d = a[i][col];
                c = i;
            }
        if (c != col)
        {
            swap(a[c], a[col]);
            swap(b[c], b[col]);
        }
    }
    void debug()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n + 1; j++)
                if (j < n)
                    cout << a[i][j] << " ";
                else
                    cout << b[i] << "\n";
    }

public:
    Gauss() {}
    Gauss(int n, vector<vd> c, vd d)
    {
        this->n = n;
        a = c, b = d;
    }
    void getData()
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            vd now;
            for (int j = 0; j < n + 1; j++)
            {
                double x;
                cin >> x;
                if (j == n)
                    b.emplace_back(x);
                else
                    now.emplace_back(x);
            }
            a.emplace_back(now);
        }
    }
    void run()
    {
        for (int k = 0; k < n - 1; k++)
        {
            choose(k);
            for (int i = k + 1; i < n; i++)
                a[i][k] /= a[k][k];
            for (int i = k + 1; i < n; i++)
                for (int j = k + 1; j < n; j++)
                    a[i][j] -= a[i][k] * a[k][j];
            for (int i = k + 1; i < n; i++)
                b[i] -= a[i][k] * b[k];
        }
        b[n - 1] /= a[n - 1][n - 1];
        //debug();
        for (int i = n - 2; i >= 0; i--)
        {
            double c1 = 1 / a[i][i];
            double sum = 0;
            for (int j = i + 1; j < n; j++)
                sum += a[i][j] * b[j];
            b[i] = c1 * (b[i] - sum);
        }
    }
    void print()
    {
        for (int i = 0; i < n; i++)
            cout << "x" << i + 1 << "=" << b[i] << "\n";
    }
};
int main(int argc, char const *argv[])
{
    Gauss g;
    g.getData();
    g.run();
    g.print();
    return 0;
}
/*
3
1 2 3 1
5 4 10 0
3 -0.1 1 2

3
12 -3 3 15
-18 3 -1 -15
1 1 1 6
 */