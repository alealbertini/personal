#include <iostream>

using namespace std;

int main()
{
   string palabra1,palabra2;
   cin >> palabra1;
   cin >> palabra2;
   bool esMenor=false,esMayor=false;

   for(int i=0;i<palabra1.size() && !esMenor && !esMayor;i++){
        if((palabra1[i]>=65 && palabra1[i]<=90 && palabra2[i]>=65 && palabra2[i]<=90 && palabra1[i] < palabra2[i]) || (palabra1[i]>=65 && palabra1[i]<=90 && palabra2[i]>=91 && palabra2[i]<=122 && palabra1[i]+32 < palabra2[i]) ||
           (palabra1[i]>=91 && palabra1[i]<=122 && palabra2[i]>=65 && palabra2[i]<=90 && palabra1[i] < palabra2[i]+32) || (palabra1[i]>=91 && palabra1[i]<=122 && palabra2[i]>=91 && palabra2[i]<=122 && palabra1[i] < palabra2[i])){
                    esMenor = true;
        }else if((palabra1[i]>=65 && palabra1[i]<=90 && palabra2[i]>=65 && palabra2[i]<=90 && palabra1[i] > palabra2[i]) || (palabra1[i]>=65 && palabra1[i]<=90 && palabra2[i]>=91 && palabra2[i]<=122 && palabra1[i]+32 > palabra2[i]) ||
                 (palabra1[i]>=91 && palabra1[i]<=122 && palabra2[i]>=65 && palabra2[i]<=90 && palabra1[i] > palabra2[i]+32) || (palabra1[i]>=91 && palabra1[i]<=122 && palabra2[i]>=91 && palabra2[i]<=122 && palabra1[i] > palabra2[i])){
                    esMayor = true;
                }
   }

   if(esMenor){
        cout << -1;
   }else if(esMayor){
        cout << 1;
   }else{
        cout << 0;
   }

}
