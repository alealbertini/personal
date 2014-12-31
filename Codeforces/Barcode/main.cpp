#include <iostream>

using namespace std;

int n,m,x,y;
int costos[2][2000];
int costosCalculados[2][2000][2000];

int recursiva(int n, int m, int x, int y, int pos, bool blanca) {
    int costoDeEste, costoDeLosDemas, costo, minimo;

    //Y si el ultimo no entra?
    if (pos + x > m) return 9999999;

    for (int i=x;(i<=y) && (pos + i <= m);i++) {
        if (costosCalculados[blanca][pos][i-x] != -1) {
            costo = costosCalculados[blanca][pos][i-x];
        } else {
            costoDeEste = 0;
            for (int j=0;j<i;j++) {
                costoDeEste += costos[blanca][pos + j];
            }
            if (pos + i < m) {
                costoDeLosDemas = recursiva(n, m, x, y, pos + i, not(blanca));
                costo = costoDeEste + costoDeLosDemas;
            } else {
                costo = costoDeEste;
            }
            costosCalculados[blanca][pos][i-x] = costo;
        }

        if (i==x || costo < minimo) minimo = costo;
    }

    return minimo;
}

int main()
{
    cin >> n >> m >> x >> y;

    for (int j=0;j<m;j++) {
        for (int k=0;k<y-x+1;k++) {
            costosCalculados[0][j][k] = -1;
            costosCalculados[1][j][k] = -1;
        }
    }

    string fila;

    for (int i=0;i<n;i++) {
        cin >> fila;
        if (i==0) {
            for (int j=0;j<m;j++) {
                costos[0][j] = 0;
                costos[1][j] = 0;
                if (fila[j] == '.') {
                    costos[0][j]++;
                } else {
                    costos[1][j]++;
                }
            }
        } else {
            for (int j=0;j<m;j++) {
                if (fila[j] == '.') {
                    costos[0][j]++;
                } else {
                    costos[1][j]++;
                }
            }
        }
    }

    int minblanco, minnegro;

    minblanco = recursiva(n,m,x,y,0,true);
    minnegro = recursiva(n,m,x,y,0,false);

    if (minblanco < minnegro) {
        cout << minblanco << endl;
    } else {
        cout << minnegro << endl;
    }

}
