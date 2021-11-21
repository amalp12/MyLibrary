/*
Codeforces Sample Problem Solving By Rachit Jain
Problem Link: https://codeforces.com/contest/808/problem/D

*/
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef vector <ll> vl;


int main()
{
    ll n, sum=0, sdash=0;
    cin >> n;
    vl A(n+5,0);
    // Taking in array values
    for(int i=0;i<n;i++)
    {
        cin>> A[i];
        sum+= A[i];
    }
    // if the sum is odd then the answer won't exist
    if(sum&1)
    {
        cout<< "NO"<<endl;
        return 0;
    }       
     
    map <ll, int> first , second; 
    first[A[0]]=1;

    for( ll i=1; i<n;i++) second[A[i]]++;

    // Sum of first i elements
    for( ll i=0;i<n;i++)
    {
        sdash +=A[i];
        if(sdash == sum/2)
        {
            cout<< "YES"<<endl;
            return 0;   
        }
        if (sdash <sum/2)
        {
            ll x = sum/2 - sdash;
            // delete element from second half and insert into first half.

            // if the element x exists in the second half then print yes
            if(second[x]>0)
            {
                cout<< "YES"<<endl;
                return 0;   
            }
        }
        else //if (sdash >sum/2)
        {
            ll y = sdash-sum/2 ;
            // delete element from first half and insert into second half.

            // if the element x exists in the first half then print yes
            if(first[y]>0)
            {
                cout<< "YES"<<endl;
                return 0;   
            }
        }
    // moving to i+1
    first[A[i+1]]++;
    second[A[i+1]]--;
    }

    cout << "NO" << endl;
    return 0;
}