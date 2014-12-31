#include <iostream>

using namespace std;

int a[5];

int main()
{
    int n,x,res=0,aux;
    cin >> n;
    for(int i=0;i<n;i++){
       cin >> x;
       a[x]++;
    }
    res = a[4]+(a[2]/2)+min(a[1],a[3]);
    a[4]=0;
    a[2]=a[2]-(a[2]/2)*2;
    aux=min(a[1],a[3]);
    a[3]-=aux;
    a[1]-=aux;
    res+=a[2];
    if(a[1]==0){
        res+=a[3];
    }else{
        res+=a[1]/4;
        res+=a[1]%4;
    }
    cout << res;
}
