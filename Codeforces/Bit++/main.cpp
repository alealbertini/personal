#include <iostream>

using namespace std;

string a[150];

int main()
{
    int n,sumo1=0,resto1=0,x=0;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }

    for(int i=0;i<n;i++){
        if(a[i] == "++X" || a[i] == "X++"){
            sumo1++;
        }

        if(a[i] == "--X" || a[i] == "X--"){
            resto1++;
        }
    }

    x = sumo1 - resto1;

    cout << x;
}
