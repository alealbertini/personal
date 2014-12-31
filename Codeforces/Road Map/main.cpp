#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> ciudades[60000];
int respuesta[60000];

void calculo (int anterior, int actual) {
    if (anterior != 0) {
        respuesta[actual] = anterior;
    }

    for (int i=0; i < (int)ciudades[actual].size(); i++) {
        if (ciudades[actual].at(i) != anterior) {
            calculo(actual,ciudades[actual].at(i));
        }
    }
}

int main()
{
    //Acelera el cout (pero da problemas si uso el cout y el printf)
    ios_base::sync_with_stdio(false);

    int n, r1, r2;

    cin >> n >> r1 >> r2;

    int aux;

    for (int i=1;i<n;i++) {
        cin >> aux;
        if (i < r1) {
            ciudades[i].push_back(aux);
            ciudades[aux].push_back(i);
        } else {
            ciudades[i+1].push_back(aux);
            ciudades[aux].push_back(i+1);
        }
    }

    calculo(0,r2);

    for (int i=1;i<=n;i++) {
        if (i != r2) {
            cout << respuesta[i] << " ";
        }
    }

    return 0;
}
