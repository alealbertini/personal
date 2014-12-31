#include <iostream>

using namespace std;

int mcd(int a,int b){
    if(a==0){
        return b;
    }else{
        return mcd(b%a,a);
    }
}

int main()
{
    int a,b,n,acum=0;
    cin >> a >> b >> n;

    for(int i=0;n>0;i++){
        if(i%2==0){
            n = n - mcd(a, n);
            acum++;
        }else{
             n = n - mcd(b, n);
             acum++;
        }
    }

    if(acum%2==0){
        cout << 1;
    }else{
        cout << 0;
    }
}
