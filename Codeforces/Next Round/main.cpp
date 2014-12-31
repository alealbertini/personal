#include <iostream>

using namespace std;

int main()
{
    int n,k,nat,res=0;
    bool esPosible = true;

    cin >> n >> k;

    int a[n];

    for(int i=0;i<n;i++){
        cin >> nat;
        a[i] = nat;
    }

    if(a[0] == 0){
        res = 0;
        esPosible = false;
    }

    for(int i=0;i<n && esPosible;i++){
        if(a[i] >= a[k-1] && a[i] != 0){
            res++;
        }else{
            esPosible = false;
        }
    }

    cout << res;
}
