#include <stdio.h>
#include <math.h>

#include <stdlib.h>

int *  create_array(int n)
{
	int * arr = (int *) malloc(sizeof(int) *n);
	for(int i = 0 ; i < n; i++)
	{
		arr[i] = 0;
	}
	return arr;
} 

int *  take_input_array(int * arr , int n)
{
	
	for(int i = 0 ; i < n; i++)
	{
		scanf("%d ", &arr[i]);
	}
	return arr;
} 



void print_array(int * arr, int n )
{
	int flag = 0;
	int i = 0;
	for(; i < n; )
	{
		if(arr[i]!=0)
		{
			flag = 1;
			break;
		}
		i++;
		
	}	
	for(; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	if(flag==0) printf("0");
	printf("\n");

}
int *  get_array(int n){

	int * array = create_array(n);
	array = take_input_array(array, n);
	return array;
	

}

int max(int a, int b)
{
	if(a>b) return a;
	else return b;
}

int min(int a, int b)
{
	if(a<b) return a;
	else return b;
}

int * add(int * arr1, int * arr2 ,int n,int  m)
{
	int new_len = max(n,m)+1;
 	int * ans = create_array(new_len);
	int first = n-1;
	int second = m-1;
	int temp;
	int rem = 0;
	int new_pos = new_len -1;
	while(first>=0 && second>=0)
	{
		temp = arr1[first]+arr2[second]+ rem;
		ans[new_pos] = (temp%7);
		rem = temp/7;
		first--; second--; new_pos--;
				
	}
	while(second>=0)
	{	
		temp = arr2[second]+rem ;
		ans[new_pos] = (temp%7);
		rem = temp/7;
		second--; new_pos--;
		
	
	}
	while(first>=0)
	{
		temp = arr1[first]+rem ;
		ans[new_pos] = (temp%7);
		rem = temp/7;
		first--; new_pos--;
		
	
	}
	if(rem!=0) ans[new_pos] = rem ;
	return ans;



}

int main()
{
	int n,m; 
	scanf("%d", &n);
	scanf("%d", &m);

	// getting array 1
	int * num1 = get_array(n);
	int * num2 = get_array(m) ;
	int * ans = add(num1, num2, n,m);


	print_array(ans,max(n,m)+1);
	return 0;
}

