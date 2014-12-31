#include <iostream>

using namespace std;

int datos[30];

int main()
{
    int k;
    string palabra;

    cin >> k;
    cin >> palabra;

    for (int i=0; i<30; i++) {
        datos[i] = 0;
    }

    int aux;
    for (int i=0;i < (int)palabra.length();i++) {
        aux = palabra[i];
        datos[aux-97]++;
    }

    bool termino = false;
    string salida = "";
    char auxC;

    for (int i=0; i<30 && !termino; i++) {
        if (datos[i] != 0) {
            if (datos[i] % k == 0) {
                auxC = i+97;
                for (int j=0; j < datos[i] / k; j++) {
                    salida += auxC;
                }
            } else {
                termino = true;
            }
        }
    }

    string salidaTotal = "";

    if (!termino) {
        for (int i=0;i < k;i++) {
            salidaTotal += salida;
        }
        cout << salidaTotal << endl;
    } else {
        cout << "-1" << endl;
    }
}
