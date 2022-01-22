int isPrime(int num )
{
    // if the number is less than 2 return false
    if(num<2) return 0;
    // 2 is the only even prime number
    if(num==2) return 1;
    // all other even numbers are not prime
    if(num%2==0) return 0;
    // now we know that num is odd and greater than 2 so we need to check only till sqrt(num)
    for(int i = 3; i<=sqrt(num); i+=2) if(num%i==0) return 0;
    return 1;
}
// returns the largest prime less than num
int largestPrime(int num )
{
    int curr = num-1;
    while(!isPrime(curr)) curr--;
    return curr;
}
