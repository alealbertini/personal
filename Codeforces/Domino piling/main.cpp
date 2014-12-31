#include <iostream>

using namespace std;

int main()
{
   int m,n,res=0;
   cin >> m >> n;

   if(n%2==0 && m%2==0){
        res = (n/2*m);
        cout << res;
   }

   if((n%2==1 && m%2==0) || (n%2==1 && m%2==1)){
        res = m/2+(m*(n/2));
        cout << res;
   }

    if(n%2==0 && m%2==1){
        res = (m*(n/2));
        cout << res;
   }
}
