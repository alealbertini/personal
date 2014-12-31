#include <iostream>

using namespace std;

//Da timeout. Se podria guardar en base a que empleados se usaron y que numero estoy mirando si es posible o no, pero considerando que
//lo hacen con 30000 empleados no se si da ... Se podria hacer con un numero menor que algo es algo, pero aun asi es raro.

//Una opcion es considerar un array que solo mire si los primeros 2 o 3 son iguales, y eso reduce en 2 o 3 veces el tiempo, pero me puteaba, hay que ver bien, deberia andar.

//es [d,d], maximo 100000, pero si pongo tanto explota y de alguna forma anda igual O_o;
int siguiente[2000][2000];
//es e, maximo 30000, idem arriba;
bool usados[2000];
int resultado[2000];

int res(int e, int d, int pos, int anterior) {
    for (int i=1;i<=e;i++) {
        if ((usados[i] == false) && ((anterior == -1) || (siguiente[anterior][i] == 1))) {
            usados[i] = true;
            resultado[pos] = i;
            if (pos == e) {
                return 1;
            } else {
                if (res(e,d,pos+1,i) == 1) {
                    return 1;
                } else {
                    usados[i] = false;
                }
            }
        }
    }

    return -1;
}

int main()
{
    int e, d;

    cin >> e >> d;

    for (int i=1;i<=e;i++) {
        for (int j=1;j<=e;j++) {
            siguiente[i][j] = 1;
        }
        usados[i] = false;
        resultado[i] = -1;
    }

    int p,q;
    for (int i=0;i<d;i++) {
        cin >> p >> q;
        siguiente[p][q] = 0;
    }

    int aux;

    aux = res(e,d,1,-1);

    //Ver si concatenar string antes de sacarlo !!!
    if (aux == 1) {
        for (int i=1;i<=e;i++) {
            cout << resultado[i] << " ";
        }
    } else {
        cout << "-1" << endl;
    }

}
