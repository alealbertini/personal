#include <iostream>

using namespace std;

int salida[1000];

int main()
{
    //Acelera el cout (pero da problemas si uso el cout y el printf)
    ios_base::sync_with_stdio(false);

    bool termino = false;
    double n;
    int res;
    double c;

    int i;
    for (i=0;!termino;i++) {
        cin >> n;

        if (n!=-1) {
            res = 0;
            for (int a=n;a>0;a--) {
                for (int b=min(int(n/a),a);b>=0;b--) {
                    c = (n-a*b)/(a+b);
                    if ((c >= 0) && (c - (int)c == 0) && (c <= b)) {
                        res++;
                    }
                    //cout << n << "//" << a << "//" << b << "//" << c << "//" << res << endl;
                }
            }

            salida[i] = res;
        } else {
            termino = true;
        }
    }

    for (int j=0;j<i-1;j++) {
        cout << salida[j] << endl;
    }
}
