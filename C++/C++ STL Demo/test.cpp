#include <iostream>
#include <vector> 
using namespace std;
typedef vector<long long> vl ;
typedef long long ll; 

int main() 
{   
    ll n, sum=0;
    cin >> n;
    vl a(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        sum+=a[i];
    }
    
    for(int i : a)
        cout << a[i] <<"\t" <<endl;
        
        
    return 0;
}   
