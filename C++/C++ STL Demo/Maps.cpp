#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
#define size 5

template <typename T>
T print( T x)
{
    cout << x<< endl;
}



int main()
{
    // C++ STL
    // Defining Maps
    /*
    One data is mapped to another data, the two datatypes of the maps can also be different.

    */
   // Each of these mappings take log(N) time to insert and also the same to retrive 
   map<int, int> M;
   M[1]=100;
   M[2]=-1;
   M[3]=200;
   M[100000232]=1;

   map<char, int> cnt;
   string x ="Amal Prakash";
    // Finding the number of times a charecter of occurrs
    /*
    Here we try to find the number of times the letters 'a' and 'z' occurs.
    */
   for(char c: x)
   {
       cnt[c]++;
   }
   cout << cnt['a'] << " " << cnt['z'] << endl;


    
    return 0;
}