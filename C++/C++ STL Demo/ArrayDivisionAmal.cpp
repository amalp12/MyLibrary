#include <iostream>
#include <vector> 
using namespace std;
typedef vector<long long> vl ;
typedef long long ll; 
//Failed code
int main() 
{   
    ll n, sum=0, temp=0, index;
    cin >> n;
    vl a(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        sum+=a[i];
    }
    if (sum%2!=0)
    {
        cout <<"NO" << endl;
        return 0;
    }
    /*
    for(ll i : a)
        cout << i <<"\t" <<endl;
    */
    for(ll i =0; i<n;i++)
    {
        temp += a[i];
        if(temp == sum/2)
        {
            cout <<"YES"<< endl;
            return 0;
        }
        else if(temp>sum/2)
        {
            index=i;
            break;
        }
        
    }
    temp = (sum-temp)/2;
    for(ll i=0; i<index; i++)
    {
        if(temp == a[i])
        {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    //cout << sum <<"\t" <<endl;    
    return 0;
}   
