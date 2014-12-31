#include<iostream>

char matriz[300][300];

using namespace std;

int main()
{
    int n;
    cin >> n;
    string s;
    for(int i=0;i<n;i++){
        cin >> s;
        for(int j=0;j<(int)s.length();j++){
            matriz[i][j] = s[j];
        }
    }
    int k = matriz[0][0];
    bool esIgual = true;
    for(int i=0;i<n && esIgual;i++){
            if(matriz[i][i] != k){
                esIgual=false;
            }else{
                matriz[i][i]='.';
            }
    }
    //cout << "1:" << esIgual << endl;

           int i=0,j=n-1;
            while(i<=n-1 && j>=0){
                    if(matriz[i][j] != k && i!=j){
                        esIgual=false;
                    }
                    //cout << i << "," << j << ":" << esIgual << endl;
                matriz[i][j] = '.';
                i++;
                j--;
            }
            //cout << "2:" << esIgual << endl;

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                //cout << matriz[i][j] << "/";
            }
            //cout << endl;
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(matriz[i][j]!='.' && (matriz[i][j] == k || matriz[i][j]!=matriz[0][1])){
                    esIgual=false;
                }
            }
        }
        //cout << "3:" << esIgual << endl;
        //cout << "valor k:" << k;

    if(!esIgual){
        cout << "NO";
    }else{
        cout << "YES";
    }
}
