#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    string hello = "hello";
    string palabra;

    cin >> palabra;

    int longitud = palabra.length();

    int j=0;
    for (int i=0;i<longitud && j < 5;i++) {
        if (palabra[i] == hello[j]) {
            j++;
        }
    }

    if (j==5) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
