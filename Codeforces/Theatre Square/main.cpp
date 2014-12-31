#include <iostream>

using namespace std;

int main()
{
    long long n,m,a,res=0,res1=0,res2=0;

    cin >> n >> m >> a;

    res1 = n / a;
    res2 = m / a;

    if(n != res1*a){
        res1++;
    }

    if(m != res2*a){
        res2++;
    }

    res = res1*res2;

    cout << res;

}
