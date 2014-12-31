#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string a[100];

int main()
{
    int n,b;
    char x,c;
    string s;
    cin >> n;

    for(int i=0;i<n;i++){
        cin >> a[i];
    }

    for(int i=0;i<n;i++){
        if(a[i].size() <= 10){
           cout << a[i] << endl;
        }else{
            stringstream sstm;
            x = a[i][0];
            b = a[i].size()-2;
            c = a[i][a[i].size()-1];
            sstm << x << b << c;
            //s = (char)()+(int)(a[i].size()-2)+(char)(a[i][a[i].size()-1]);
            cout << sstm.str() << endl;
        }
    }



}
