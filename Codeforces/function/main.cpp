#include <iostream>

using namespace std;

int main()
{
    int y,x=0,i=0;
    cin >> y;

    while(x!=y){
        x = i^(i/2);
        i++;
    }

    cout << x;

}
