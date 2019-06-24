#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
int a[4][4] ={{1,2,3},{4,5,6},{7,8,9}};
int main() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin>>a[i][j];
            cout<<" ";
        }
        cout<<endl;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout<<a[j][i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
