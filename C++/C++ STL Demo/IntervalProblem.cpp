#include <iostream>
#include <set>
#include <algorithm>
using namespace std;




/*
Input 1: A collection of intergers x and y that are pairs and denote an interval between them
        Note that no integer interval in a given test case overlaps.
Input 2: A single integer z.

Output : print the pair exact pair of interval numbers that contains z. if not found then print " Not Found ".
"

Note:
    The values in any pair X = {a,b} can be accessed using X.first and X.second. 

*/

int main()
{

    /*
    
    Pair {a,c} is smaller than Pair {b,d} if and only if 
    Case 1 : (a<b)
    Case 2: (a==b) and (c<b)


    In simple words we can say that while soring pairs, first pairs are sorted according to all their X coordinates only, and when
    their X coordinates turn out to to be the same then their Y coordinates are compared.   
        */

    // In our case the X coordinates are always different so we do not have to worry about the Y coordinates.
    set <pair<int, int>> S;
    S.insert({401,450});
    S.insert({10,20});
    S.insert({2,3});
    S.insert({30,400});

    // Printing the elements in the set
    for( pair<int,int> x: S)
        cout << "{ "<< x.first<<", "<<x.second<<" } " <<"\t";
    cout <<endl; 
    /*
    While iterating and comparing also the same logic is followed, first all X coordinates are compared and iff they turn out to be equal only then
    Y coordnates are compared. 

    upperbounding on a pair should give a the number that is strictly greater than given number's interval, but something more intersesting happens


    Let us understand this by taking the following intervals and giving 10 as an arguement to upper bound, inside the function it becomes {10,0}
    {401,450}
    {10,20}
    {2,3}
    {30,400}

    Here, we might think that upperbounding {10,0} shouldn't return the interval {10,20} as upper bounding only returns elements which are stricly greater than the
    arguement provided. 
    But we should also consider that the pair inequality {10,0}<{10,20} stands true, recall that once the X coordinates are found to be equal then Y coordnates are comapared (0<10)
    hence makes the pair inequality {10,0}<{10,20} true and it will in reality return {10,20}.


    But we don't take it like we mentioned above, because let in a case where 50 lies in the interval {30,400}, this interval is neglected as {50,0}>{30,400}

    Hence we come up with another logic,
    we take the upper bound of {50, INT_MAX} and then get an interval which 50 is not in defintely , and then iterate backwards using -- operator.
    
    */

    // lets take a number for testing and dehugging
    int point = 50;
    // INT32_MAX is the maximum integer value a 32 bit binacry code can hold.
    auto it = S.upper_bound({50, INT32_MAX});//<=
   
    pair<int, int> current = *it;
    /*
    Also we have to tackle a corner case where input is 1, the it pointer goes to the first element and then does it--, which wil result in wrong output.
    so we make an if statement for this corner case.
    */ 

    if (it == S.begin())
    {
        cout << "The given point is not lying in any interval." << endl; 
        return 0;
    }
    it--; // Iterating backwards

    cout <<"Closest Interval Found : " <<current.first << "\t" << current.second<< endl; // printing the interval we got

    
        
    if (point>= current.first and point<= current.second)
    {
        cout << "Yes, its present : " << current.first << "\t" << current.second << endl;

    }
    else 
        cout << "The given point is not lying in any interval." << endl;
        


    

}   