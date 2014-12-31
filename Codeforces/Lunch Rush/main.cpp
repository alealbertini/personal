#include <iostream>

using namespace std;

int matriz[10000][2];

int main()
{
    int n,k;
    cin >> n >> k;
    for(int i=0;i<n;i++){
        cin >> matriz[i][0] >> matriz[i][1];
    }

    int maximo=-999999999;
    for(int i=0;i<n;i++){
        if(matriz[i][1] > k){
            maximo = max(maximo, matriz[i][0] - (matriz[i][1] - k));
        }else{
            maximo = max(maximo, matriz[i][0]);
        }
    }
    cout << maximo;

}
