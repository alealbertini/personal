#include <iostream>

using namespace std;

int a[1000][1000];
int res[1000];

int main()
{
    int n;

    cin >> n;

    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1 ;j++){
            cin >> a[i][j];
        }
    }

    for(int i=0; i<n; i++){
        res[i] = 1;
    }


    for(int i=0; i<n-1; i++){
            int l = i;
        for(int j=0; j<n-i-1; j++){

            while(!(res[l] % a[i][j] == 0 && res[j+l+1] % a[i][j] == 0)){

                if(!(res[l] % a[i][j] == 0)){
                    res[l] = res[l] + min(res[l], res[j+l+1]);
                }

                if(!(res[j+l+1] % a[i][j] == 0)){
                    res[j+l+1] = res[j+l+1] + min(res[l], res[j+l+1]);
                }
            }
        }
    }

    for(int i=0; i<n; i++){
        cout << res[i] << " ";
    }

}
