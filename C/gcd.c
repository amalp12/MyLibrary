

// recursive 
int gcd(int m,int n)
{
    m = abs(m); n = abs(n);
    if (n==0) return m;
    else return gcd(n, m%n);
}

// non recursive
int gcd(int a, int b)
{
    int c;
    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}
