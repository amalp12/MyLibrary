// function to find m raised to n
int power(int n, int m)
{
    int answer = 1;
    while(m>0)
    {
        answer*=n;
        m--;
    }
    return answer;
    
}