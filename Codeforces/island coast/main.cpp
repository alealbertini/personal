#include <iostream>

using namespace std;

char matriz[1000][1000];

int main()
{
    int n,m, res=0;

    cin >> n >> m;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> matriz[i][j];
        }
    }

    for(int j=0;j<m;j++){
        if(matriz[0][j] == '+'){
            res++;
        }
    }

    for(int j=0;j<m;j++){
        if(matriz[n-1][j] == '+'){
            res++;
        }
    }

    for(int i=0;i<n;i++){
        if(matriz[i][0] == '+'){
            res++;
        }
    }

    for(int i=0;i<n;i++){
        if(matriz[i][m-1] == '+'){
            res++;
        }
    }

    for(int i=1;i<n-1;i++){
        for(int j=1;j<m-1;j++){
            if(!(matriz[i][j] == '+' && matriz[i+1][j] == '+' && matriz[i][j+1] == '+' && matriz[i][j-1] == '+' && matriz[i-1][j] == '+') && matriz[i][j] != '-'){
                res++;
            }
        }
    }

    cout << res << endl;
    int x=15/2;
    cout << x;

}
