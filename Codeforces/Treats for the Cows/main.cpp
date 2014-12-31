#include <iostream>

using namespace std;

int precios[3000];
int cantidad;
int ganancia[3000][3000];

int calcular(int i, int j, int dia) {
    int gananciaAux;

    if (j >= i) {
        if (ganancia[i][j] == -1) {
            ganancia[i][j] = max(precios[i]*dia + calcular(i + 1, j, dia + 1), precios[j]*dia + calcular(i, j - 1, dia + 1));
        }
        return ganancia[i][j];
    } else {
        return 0;
    }
}

int main()
{
    cin >> cantidad;

    //Hay algun problema en la logica, por ej el caso 10000 1 1 8000 8000 1

    for (int i=0;i<cantidad;i++) {
        cin >> precios[i];

        for (int j=0;j<cantidad;j++) {
            ganancia[i][j] = -1;
        }
    }

    cout << calcular(0,cantidad-1,1);

    //Este return parece que era necesario para SPOJ (aunq en ese momento el cout de arriba era un return y eso no estaba muy bien, asi q no se bien por q me daba
    //un error NZEC

    return 0;
}
