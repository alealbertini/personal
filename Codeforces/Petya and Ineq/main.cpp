#include <iostream>
#include <math.h>

using namespace std;

//100.000 810.000.099.998 1.000.000

int main()
{
    long long n, x, y;

    cin >> n >> x >> y;

    long long num;

    num = y - (n-1);

    //int acum = 0;

    if (num > 0) {
        if ((n-1 + pow(num,2)) >= x) {
            for (int i=0;i<n-1;i++) {
                cout << "1" << endl;
                //acum++;
            }
            cout << num << endl;
        } else {
            cout << "-1";
        }
    } else {
        cout << "-1";
    }
}
