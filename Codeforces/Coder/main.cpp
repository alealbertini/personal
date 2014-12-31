#include <iostream>

using namespace std;

int main()
{
    int n;
    string aux;

    cin >> n;

    if (n==1) {
        cout << "1" << endl;
        cout << "C" << endl;
    } else {
        cout << (n*n+1)/2 << endl;
        for (int i=1;i<=n;i++) {
            aux = "";
            for (int j=1;j<=n;j++) {
                if ((i+j) % 2 ==0) {
                    aux = aux + "C";
                } else {
                    aux = aux + ".";
                }
            }
            cout << aux << endl;
        }
    }
}
