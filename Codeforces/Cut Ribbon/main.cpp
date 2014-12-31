#include <iostream>

using namespace std;

//100 23 15 50

int a, b, c;
int datos[5000];

int calculo(int queda) {
    if (datos[queda] != -2) return datos[queda];

    if (queda > 0 && queda < a && queda < b && queda < c) {
        datos[queda] = -1;
        return -1;
    } else if (queda == 0) {
        return 0;
    }

    int auxA, auxB, auxC, auxMax;

    auxA = -1;
    auxB = -1;
    auxC = -1;

    if (queda >= a) {
        auxA = calculo(queda-a);
        if (auxA != -1) {
            auxA++;
        }
    }
    if (queda >= b) {
        auxB = calculo(queda-b);
        if (auxB != -1) {
            auxB++;
        }
    }
    if (queda >= c) {
        auxC = calculo(queda-c);
        if (auxC != -1) {
            auxC++;
        }
    }
    auxMax = max(auxA,max(auxB,auxC));
    datos[queda] = auxMax;
    return auxMax;
}


int main()
{
    int n,aux;

    //53 10 11 23
    //4000 1 2 3

    cin >> n >> a >> b >> c;

    for (int i=1;i<=n;i++) {
        datos[i] = -2;
    }

    if (a > b) {
        aux = a;
        a = b;
        b = aux;
    }
    if (b > c) {
        aux = c;
        c = b;
        b = aux;
    }
    if (a > b) {
        aux = a;
        a = b;
        b = aux;
    }

    cout << calculo(n);

    /*for (int i=0;i<n;i++) {
        cout << i+1 << "/" << datos[i] << endl;
    }*/

    return 0;
}
