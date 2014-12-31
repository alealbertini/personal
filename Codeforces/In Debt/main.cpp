#include <iostream>

using namespace std;

int main()
{
    bool termino = false;

    int n;
    int deuda;
    int aux;
    int visitas[100];
    int j;

    for (int i = 0;i<100;i++) {
        visitas[i] = 0;
    }

    j = 0;
    while (!termino) {
        cin >> n;
        if (n != -1) {
            deuda = 0;
            for (int i=0;i<n;i++) {
                cin >> aux;
                deuda += aux;
                if (deuda % 100 == 0) {
                    visitas[j]++;
                    deuda = 0;
                }
            }
            j++;
        } else {
            termino = true;
        }
    }

    for (int i=0;i<j;i++) {
        cout << visitas[i] << endl;
    }

    return 0;
}
