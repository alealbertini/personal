#include <iostream>

using namespace std;

int main()
{
    int n, V;
    double prop[20];
    double vol[20];
    double vololla[20];
    double sumaprop;

    cin >> n >> V;

    sumaprop = 0;
    for (int i=0;i<n;i++) {
        cin >> prop[i];
        sumaprop += prop[i];
    }
    for (int i=0;i<n;i++) {
        prop[i] = prop[i] / sumaprop;

        cin >> vol[i];

        vololla[i] = V * prop[i];
    }
    double ajuste = 1;
    for (int i=0;i<n;i++) {
        if (vololla[i]*ajuste > vol[i]) {
            //ajuste = ajuste * (vol[i]/(vololla[i]*ajuste));
            ajuste = vol[i]/vololla[i];
        }
    }

    cout << ajuste * V;

    return 0;
}
