#include <iostream>

using namespace std;

int main()
{
    string palabra;
    cin >> palabra;
    bool res = false;

    for(int i=0;i<palabra.size() && !res;i++){
        if(palabra[i]=='H' || palabra[i]=='Q' || palabra[i]=='9'){
               res = true;
        }
    }

    if(res == true){
        cout << "YES";
    }else{
        cout << "NO";
    }
}
