#include <iostream>

using namespace std;

int main()
{
    int n;
    string m;
    cin >> n;
    string s;
    cin >> s;
    /*for(int i=0;i<n;i++){
        cin >> m;
        s+=m;
    }*/

    bool esLucky=true;
    int izq=0,der=0;
    for(int i=0;i<(int)s.length() && esLucky;i++){
        if(!(s[i]=='4' || s[i]=='7')){
            esLucky=false;
        }
        if(i<(n/2)){
            izq+=s[i];
        }else{
            der+=s[i];
        }
        //cout << i << "/" << izq << "/" << der << "/" << esLucky << endl;
    }
    /*for(int i=0;i<s.length();i++){
        cout << s[i] << ",";
    }*/

    if(esLucky && izq==der){
        cout << "YES";
    }else{
        cout << "NO";
    }

}
