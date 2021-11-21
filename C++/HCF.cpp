/*
Snippet to find the Greatest Common Divisor (GSD)/Highest Common Factor(HCF)
using C++
*/

int gcd(int x, int y)
{
  if(y == 0)
      return x;
  else
      return gcd(y, x % y);
}
