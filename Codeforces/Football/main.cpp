#include <iostream>

using namespace std;

int main()
{
   string input;
   cin >> input;
   int acum=1;
   bool esPeligrosa = false;

   for(int i=0;i<input.size()-1 && !esPeligrosa;i++){
        if(input[i] == input[i+1]){
            acum++;
        }else{
            acum = 1;
        }

        if(acum == 7){
            esPeligrosa = true;
        }
    }

    if(esPeligrosa){
        cout << "YES";
    }else{
        cout << "NO";
    }
}
