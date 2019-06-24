#include <iostream>
#include <vector>
using namespace std;
int n;
double xa;
vector<double> x, y;
int main()
{
    cin >> n >> xa;
    for (int i = 0; i <= n; i++)
    {
        double xi, yi;
        cin >> xi >> yi;
        x.emplace_back(xi);
        y.emplace_back(yi);
    }
    int k = 0;
    double ans = 0;
    while (1)
    {
        double t=1;
        for (int j = 0; j <= n; j++)
        {
            if (j == k)
                continue;
            t *= (xa - x[j]) / (x[k] - x[j]);
        }
        ans+=t*y[k];
        if (k==n)
            break;
        k++;
    }
    cout<<ans;
    return 0;
}
/*
3 1.1300
1.1275 0.1191
1.1503 0.13954
1.1735 0.15932
1.1972 0.17903
*/