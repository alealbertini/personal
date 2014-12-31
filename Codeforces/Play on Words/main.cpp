#include <iostream>
#include <math.h>

using namespace std;

int letras[30][3];
string respuestas[10000];

int main()
{
    int t, n;
    string palabra;
    char aux, aux2;
    int malasI, malasD;
    bool esPosible;

    cin >> t;

    for (int i=0; i<t; i++) {
        cin >> n;

        for (int j=0; j<30; j++) {
            letras[j][0] = 0;
            letras[j][1] = 0;
            letras[j][2] = 0;
        }

        for (int j=0; j<n; j++) {
            cin >> palabra;
            aux = palabra[0];
            letras[(int)aux - 97][0]++;
            aux2 = palabra[palabra.length()-1];
            letras[(int)aux2 - 97][1]++;

            if (aux == aux2) letras[(int)aux2 - 97][2]++;
        }

        esPosible = true;
        malasI = 0;
        malasD = 0;
        for (int j=0; j<30 && esPosible; j++) {
            if ((letras[j][0] != 0 || letras[j][1] != 0) && letras[j][0] == letras[j][2] && letras[j][1] == letras[j][2] && letras[j][2] != n) {
                esPosible = false;
            } else {
                if (letras[j][0] != letras[j][1]) {
                    if (letras[j][0] - letras[j][1] == 1) {
                        malasI++;
                        if (malasI > 1) {
                            esPosible = false;
                        }
                    } else if (letras[j][1] - letras[j][0] == 1) {
                        malasD++;
                        if (malasD > 1) {
                            esPosible = false;
                        }
                    } else {
                        esPosible = false;
                    }
                }
            }
        }

        if (esPosible) {
            respuestas[i] = "Ordering is possible.";
        } else {
            respuestas[i] = "The door cannot be opened.";
        }
    }

    for (int i=0; i<t; i++) {
        cout << respuestas[i] << endl;
    }
}
