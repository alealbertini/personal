#include <iostream>
#include <vector>

/*
Test: #19, time: 0 ms., memory: 140 KB, exit code: 0, checker exit code: 1, verdict: WRONG_ANSWER
Input

100 100

79 86

53 99

...

Output

NO

Answer

FHTAGN!

Checker Log

wrong answer 1st words differ - expected: 'FHTAGN!', found: 'NO'
*/

using namespace std;

vector<int> nodos;
vector<int> relaciones[200];
int cantidad[200];

int caminar(int inicio, int actual, int anterior) {
    //Esto camina por una cosa que ya sabes que si o si es uno o mas ciclos simple sin unirse
    if (actual == inicio) {
        return 1;
    }

    for (int i=0; i<relaciones[actual].size(); i++) {
        if (relaciones[actual].at(i) != anterior) {
            return 1 + caminar(inicio, relaciones[actual].at(i), actual);
        }
    }
}

int main()
{
    int n, m;

    cin >> n >> m;

    int a, b;

    for (int i=1; i<=n; i++) {
        nodos.push_back(i);
        cantidad[i] = 0;
    }

    for (int i=0; i<m; i++) {
        cin >> a >> b;

        relaciones[a].push_back(b);
        relaciones[b].push_back(a);

        cantidad[a]++;
        cantidad[b]++;
    }

    bool esCthulhu = true;
    bool termino = false;
    bool hayNodosConUnVecino;
    bool hayNodosConMasDeTresVecinos;
    int vecino;
    bool borrado;

    while (!termino) {
        hayNodosConUnVecino = false;
        hayNodosConMasDeTresVecinos = false;
        for (int i=nodos.size()-1; i>=0; i--) {
            if (cantidad[nodos.at(i)] == 1) {
                hayNodosConUnVecino = true;
                vecino = relaciones[nodos.at(i)].at(0);
                borrado = false;
                for (int j=0; j<relaciones[vecino].size() && !borrado; j++) {
                    if (relaciones[vecino].at(j) == nodos.at(i)) {
                        relaciones[vecino].erase(relaciones[vecino].begin() + j);
                        cantidad[vecino]--;
                        borrado = true;
                    }
                }
                nodos.erase(nodos.begin() + i);
            } else if (cantidad[nodos.at(i)] == 0) {
                //Significa que no hay ningun ciclo
                esCthulhu = false;
                termino = true;
            } else if (cantidad[nodos.at(i)] >= 3) {
                hayNodosConMasDeTresVecinos = true;
            }
        }

        //Si ya termino de borrar cosas y todavia puede ser Cthulhu
        if (esCthulhu && !hayNodosConUnVecino) {
            if (!hayNodosConMasDeTresVecinos) {
                //Aca casi estamos, la unica cosa a considerar es si quedaron varios ciclos sueltos (por lo menos 2 de 3)
                if (nodos.size() > 5) {
                    if (caminar(nodos.at(0),relaciones[nodos.at(0)].at(0),nodos.at(0)) != nodos.size()) {
                        //Si entra aca hay mas de un ciclo simple
                        esCthulhu = false;
                    }
                }
                termino = true;
            } else {
                //Hay mas de un ciclo unidos entre si => No es Cthuluh
                esCthulhu = false;
                termino = true;
            }
        }
    }

    if (esCthulhu) {
        cout << "FHTAGN!" << endl;
    } else {
        cout << "NO" << endl;
    }
}
