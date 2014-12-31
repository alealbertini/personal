#include <iostream>

using namespace std;

//-491226083 -49122610
//UDRLDURLDLLLDUDURLRDUUDDUUULUDRDRDUULURDRLLDDDLUDUURLUUDLLDULLLLDDLDDUU



int main()
{
    int a,b;
    string movimientos;

    cin >> a >> b;
    cin >> movimientos;
    /*a = -491226083;
    b = -49122610;
    movimientos = "UDRLDURLDLLLDUDURLRDUUDDUUULUDRDRDUULURDRLLDDDLUDUURLUUDLLDULLLLDDLDDUU";*/

    /*//Deberia ser Yes
    a = -771928144;
    b = -3;
    movimientos = "RUDULULDRDLLLULDDUDDDDUDULRULRUULDDDURUDLUURULLLDLLDDRDDRLRURUULRUURRUDLDLDDRLLULRRDRRLLUULUDRUUDRRD";*/

    //Yes
    /*a = 987654321;
    b = 987654321;
    movimientos = "UURRDL";*/

    bool toca = false;

    if (a!=0 || b != 0) {
        int longitud = movimientos.length();

        int maxU = 0, maxD = 0,maxR = 0,maxL = 0,x = 0,y = 0;

        for (int i=0;i<longitud;i++) {
            if (movimientos[i] == 'U') {
                y++;
                if (y > maxU) maxU = y;
            } else if (movimientos[i] == 'D') {
                y--;
                if (y < maxD) maxD = y;
            } else if (movimientos[i] == 'R') {
                x++;
                if (x > maxR) maxR = x;
            } else if (movimientos[i] == 'L') {
                x--;
                if (x < maxL) maxL = x;
            }
        }

        //Esto es porq maxD y maxL salen negativas, y yo quiero la distancia !!!
        maxD = maxD * (-1);
        maxL = maxL * (-1);

        //cout << x << "/" << y << "/" << maxU << "/" << maxD << "/" << maxL << "/" << maxR << endl;

        int cU, cD, cL, cR, cMin, cMax;

        if (x != 0 || y !=0) {
            if (x == 0) {
                cU = (b + maxD) / y;
                cD = (b - maxU) / y;
                cMin = min(cU,cD);
                cMax = max(cU,cD);
            } else if (y == 0) {
                cR = (a + maxL) / x;
                cL = (a - maxR) / x;
                cMin = min(cR,cL);
                cMax = max(cR,cL);
            } else {
                cU = (b + maxD) / y;
                cD = (b - maxU) / y;
                cL = (a - maxR) / x;
                cR = (a + maxL) / x;
                /*if (x > 0) {
                    if (y > 0) {
                        cMin = max(cR,cU);
                        cMax = min(cD,cL);
                    } else {
                        cMin = max(cU,cL);
                        cMax = min(cR,cD);
                    }
                } else {
                    if (y > 0) {
                        cMin = max(cR,cD);
                        cMax = min(cU,cL);
                    } else {
                        cMin = max(cD,cL);
                        cMax = min(cR,cU);
                    }
                }*/

                //Esto se podria arreglar todavia mas con el if comentado de arriba si estuviera bien hecho, pero no hace falta XD.
                cMin = min(min(cU,cD),min(cL,cR));
                cMax = max(max(cU,cD),max(cL,cR));
            }

            if (cMin < 0) cMin = 0;
            if (cMax < 0) cMax = 0;
        } else {
            //caso x,y = 0,0 (dio una vuelta)
            cMin = 0;
            cMax = 0;
        }

        //cout << cMin << "/" << cMax << endl;

        int xaux, yaux;

        for(int j = cMin;j <= cMax && !toca;j++) {
            xaux = j*x;
            yaux = j*y;

            if (xaux == a && yaux == b) toca = true;

            for (int i=0;i<longitud && !toca;i++) {
                if (movimientos[i] == 'U') {
                    yaux++;
                } else if (movimientos[i] == 'D') {
                    yaux--;
                } else if (movimientos[i] == 'R') {
                    xaux++;
                } else if (movimientos[i] == 'L') {
                    xaux--;
                }

                if (xaux == a && yaux == b) toca = true;
            }
        }

    } else {
        //Caso a,b = 0,0
        toca = true;
    }

    if (toca) {
        cout << "Yes";
    } else {
        cout << "No";
    }
}
