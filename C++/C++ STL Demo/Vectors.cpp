#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define size 5

template <typename T>
T print( T x)
{
    cout << x<< endl;
}

//  Comparative function for sort()
bool c(int x, int y)
{
    return (x>y);
}

void printArray(vector<int> a, int s)
{
    for(int i =0; i<s;i++)
        cout<< a[i] << "\t";
    cout <<endl;
}
int main()
{
    // C++ STL
    vector<int> A = {2,1,5,4,3};
    cout << A[2] <<endl;
    sort(A.begin(), A.end()); // O(N(logN))
    // Sorted to 1,2,3,4,5
    printArray(A,size);


    // Binary Search
    /*
    Remember that Binary search only works when the array is sorted.
    */
    // Find if an element (we take 3 and 4 here) is there
    bool present = binary_search(A.begin(), A.end(), 3);
    print(present);
    present = binary_search(A.begin(), A.end(), 6);
    print(present);


    // Insert more elements 
    // Let us insert 100
    A.push_back(100);
    printArray(A,size+1);
    // Let us add 100 three more times
    A.push_back(100);
    A.push_back(100);
    A.push_back(100);
    // 1	2	3	4	5	100	100	100	100	
    A.push_back(123);
    //1	2	3	4	5	100	100	100	100	123

    printArray(A,size+4);

    /* To the the first occurance of 100 in this vector once the array is sorted*/
    auto it = lower_bound(A.begin(),A.end(), 100) ;//vector<int> ::iterator it = lower_bound(A.begin(),A.end(), 100) ; //>=
    auto it2 = upper_bound(A.begin(),A.end(), 100) ;//vector<int> :: iterator  it2 = upper_bound(A.begin(), A.end(), 100) ; // > (returns pointer of element strictly greater than)

    cout << "it = "<< *it << "\t it2 = " << *it2 << endl;
    cout << "it2 -it = "<<*it2- *it << endl;
      
    
    /*
    Sort can also use a comparator function that returns a boolean values to compare instead of the normal sort
     
    here we define a comparator funtion c , to help us sort the data in the decending order
    */
    sort(A.begin(), A.end(),c);


    // Printing a vector
    //vector<int> :: iterator it3;

    for(int x : A)//for(it3 = A.begin(); it3 !=A.end(); it3++) // note A.end() returns an iterator one past the last element 
    {
        cout << x << "\t" ;
    }
    cout << endl;

    for(int &x : A) // Iterate and increment values in the vector y reference
    {
        x++;
    }
    printArray(A, size+4);

    return 0;
}