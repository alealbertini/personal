#include <iostream>
#include <string>

using namespace std;

char vocales[12] = {'a','e','i','o','u','A','E','I','O','U','Y','y'};

bool pertenece(char b, char a[], int n){
    bool res = false;
    for(int i=0;i<n && !res;i++){
        if(a[i] == b){
            res = true;
        }
    }
    return res;
}

int main()
{
   string p, res;
   cin >> p;
    //cout << p[1] << "-"; //<< p[1];
   for(int i=0;i<p.size();i++){
           //cout << "entro al for";
           if(!pertenece(p[i], vocales, 12) && (int)(p[i])>=97){
               //cout << "entro al if";
               res += ".";
               res += (char)p[i];
           }else if(!pertenece(p[i], vocales, 12) && (int)(p[i])<97){
                //cout << "entro al else";
                res += ".";
                res += (char)(p[i]+32);
           }
   }
    cout << res;
}
