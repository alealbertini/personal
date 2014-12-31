#include <iostream>

using namespace std;

int main()
{
    int mayus=0;
    string palabra;
    cin >> palabra;

    int n = palabra.size();

    for(int i=0;i<n;i++){
        if((int)palabra[i]>=65 && (int)palabra[i]<=90){
            mayus++;
        }
    }

    if(mayus == n){
        for(int i=0;i<n;i++){
            palabra[i] = (char)(palabra[i]+32);
        }
    }

    if(mayus == n-1 && (palabra[0]<65 || palabra[0]>90)){
        palabra[0] = (char)((int)palabra[0]-32);

        for(int i=1;i<n;i++){
            palabra[i] = (char)((int)palabra[i]+32);
        }
    }
    cout << palabra;
}
