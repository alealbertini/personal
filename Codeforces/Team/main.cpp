#include <iostream>

using namespace std;

int a[1000][3];

int main()
{
    int n;
    cin >> n;

    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            cin >> a[i][j];
        }
    }

    int acum=0,res=0;

    for(int i=0;i<n;i++){
            acum = 0;
        for(int j=0;j<3;j++){
            if(a[i][j] == 1){
                acum++;
            }
            if(j==2 && acum>=2){
                res++;
            }
        }
    }
    cout << res;
}
