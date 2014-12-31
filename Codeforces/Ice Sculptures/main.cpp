#include <iostream>
#include <vector>
#include <math.h>

/*
Problema test 26 (No es problema de n, hizo bien con cosas mas grandes)

16384

-1 0 0 -1 1 0 1 -1 1 0 0 -1 1 -1 -1 1 1 0 -1 -1 1 -1 0 1 1 0 -1 -1 1 1 1 0 -1 -1 1 1 1 -1 0 1 1 1 0 0 0 -1 -1 1 0 0 -1 -1 0 1 0 -1 0 -1 -1 -1 1 0 0 -1 -1 1 0 0 -1 1 -1 1 0 1 1 1 0 0 0 0 -1 0 0 1 1 -1 -1 1 -1 1 0 0 0 0 0 -1 1 1 0 -1 0 0 -1 -1 -1 -1 1 0 -1 0 -1 0 -1 -1 1 -1 0 0 -1 0 0 1 -1 0 -1 -1 0 0 -1 1 -1 0 1 0 1 1 0 -1 -1 -1 0 1 0 1 1 -1 1 0 1 -1 0 1 1 -1 0 -1 -1 0 1 0 1 1 -1 1 -1 0 1 -1 1 -1 0 1 -1 1 -1 1 -1 0 1 1 -1 1 0 1 0 -1 0 -1 1 -1 0 0 1 -1 0 1 0 -1 1 1 -1 -1 1 0 0 0 -1 1 -1 1 0 -1 0 -1 -1...

Output

23

Answer

73

Checker Log

wrong answer expected 73, found 23
*/

using namespace std;

int primos[150];
int cantprimos;
vector<int> puntos;

int calculo(int cantidad, int inicio, int salto) {
    int suma;
    int maximo;
    double raiz;

    suma = 0;
    for (int i=0; i < cantidad; i++) {
        suma += puntos.at(inicio + i*salto);
    }

    maximo = suma;

    //Este if sirve poq habia un problema que cuando cantidad era 4 me la dividia en 2 "rayas" y eso no estaba bien :p
    if (cantidad > 5) {
        raiz = sqrt(cantidad);
        //Aca puse <= ya que para el caso de 49agono necesito ver el numero 7
        for (int i=0; i<cantprimos && primos[i]<=raiz; i++) {
            if (cantidad % primos[i] == 0) {
                for (int j=0; j<primos[i]; j++) {
                    maximo = max(maximo, calculo(cantidad/primos[i] ,j, salto * primos[i]));
                }
            }
        }
    }

    return maximo;
}

int main()
{
    int n;
    int aux;

    cin >> n;

    for (int i=0; i<n; i++) {
        cin >> aux;
        puntos.push_back(aux);
    }

    bool esPrimo;
    cantprimos = 0;

    primos[0] = 2;
    cantprimos++;

    for (int i=3; i < 150; i+=2) {
        esPrimo = true;
        for (int j=3; j<i && esPrimo; j+=2) {
            if (i % j == 0) esPrimo = false;
        }
        if (esPrimo) {
            primos[cantprimos] = i;
            cantprimos++;
        }
    }

    cout << calculo(puntos.size(),0,1);
}
