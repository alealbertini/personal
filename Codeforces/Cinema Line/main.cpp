#include <iostream>

using namespace std;

int plata[100000];

int main()
{
    int gente;
    int billetes25 = 0;
    int billetes50 = 0;
    bool esPosible = true;

    cin >> gente;

    for (int i=0;i<gente && esPosible;i++) {
        cin >> plata[i];
        if (plata[i] == 25) {
            billetes25++;
        } else if (plata[i] == 50) {
            if (billetes25 > 0) {
                billetes50++;
                billetes25--;
            } else {
                esPosible = false;
            }
        } else {
            if (billetes50 > 0 && billetes25 > 0) {
                billetes25--;
                billetes50--;
            } else if (billetes25 > 2) {
                billetes25 -= 3;
            } else {
                esPosible = false;
            }
        }
    }

    if (esPosible) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
