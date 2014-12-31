#include <iostream>

using namespace std;

char a[50];

int main()
{
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }

    string res = ""; //agregar el primer caracter
    res += a[0];

    for(int i=1;i<n;i++){
        if(a[i-1] != a[i]){
            res += a[i];
        }
    }
    int b;
    b = n - res.size();
    cout << b;
}
