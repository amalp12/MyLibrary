#include <iostream>
#include <algorithm>
#include <set>
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
    // Defining Sets
    /*
    Sets are really convinient because it always keeps its elements in the acending order.
    Elements are inserted into a set using the insert(x) method.

    Note that sets do not allow duplicates of an element.
    */
    set<int> S ;
    S.insert(1);
    S.insert(2);
    S.insert(-1);
    S.insert(-10);
    S.insert(1); // No effect, because its already there.
    // Printing the elements in the set
    for( int  x: S)
        cout << x <<"\t";
    cout <<endl;
    // outputs : 10	-1	1	2

    // Finding a desired element from the set
    /*
    We can use the find(x) method to find a element of interest from the set.
    Note that it returns the iterator of the element when found.
    If the specified element is not found then this method returns the iterator of the end() method.
    */
   auto it = S.find(-1);
    if (it == S.end())
        cout << "Element not found in the set." << endl;
    else
        cout << "Present! Element " << *it <<" is found." << endl;
    
    // Finding the upperbound and the lowerbound 
    /*
    As Set is always sorted, we don't need to specify the begin() and end() like in vectors.
    */
   auto it2 = S.lower_bound(-1); // >=
   auto it3 = S.upper_bound(0); // >
   
   cout << "it2 = "<< *it2 << "\t it3 = " << *it3 << endl;

   auto it4 = S.upper_bound(2); // >=

    if (it4 == S.end())
        cout << "Oops ! Something went wrong, This element doesn't exist." << endl;
    /*
    We can also erase an element in log(N) time using erase(x) method.
    */
    S.erase(1);
    // Printing the elements in the set
    for( int  x: S)
        cout << x <<"\t";
    cout <<endl;
    
    return 0; 
    
}


/*
Extras

For a set of unordered_set, the insert method returns a pair iterator pointing to the element - boolean indicating where it was added or not for being already there

You can use an std::unordered_set if you want to allow records of  duplicates. There is a method insert which, depending on library version returns you information about the insertion (either a pair with a bool that is true if insertion was effective and false if already in), or an iterator, etc. Find the documentation of your lib.




*/