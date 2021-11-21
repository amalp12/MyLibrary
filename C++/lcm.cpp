int lcm(int a, int b)
{
	int l = min(a,b);
	int h = max(a,b);
    //cout<< l << " " << h<< endl;
	if( h%l==0)
	    return h;
	else
	{
		for(int i =2;i<h;i++)
		{
			if(l%i==0 and h%i==0)
			{
    			if(l>i)
    			{
				    l /= i;
    				h /= i;
    			}
    			else break;
			}
		}
		return l*h;
	}
}
