#include <iostream>

using namespace std;

int main()
{
    string palabra;
    cin >> palabra;
    int i=0;
    bool esMagico=true;
    while(i < (int)palabra.size() && esMagico){
        if(i<(int)palabra.size()-2 && palabra[i]=='1' && palabra[i+1]=='4' && palabra[i+2]=='4'){
            i+=3;
        }else if(i<=(int)palabra.size()-1 && palabra[i]=='1' && palabra[i+1]=='4'){
                 i+=2;
            }else if(palabra[i]=='1'){
                i+=1;
            }else{
                esMagico = false;
            }
    }
    if(esMagico){
        cout << "YES";
    }else{
        cout << "NO";
    }
}
