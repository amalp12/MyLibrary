


int gcd(int m,int n)
{
    m = abs(m); n = abs(n);
    if (n==0) return m;
    else return gcd(n, m%n);
}
