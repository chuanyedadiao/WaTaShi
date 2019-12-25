#include<stdio.h>


int fun(int a)
{
	int count=0;
	int b;
	while(a!=0){
		b = a%10;
		a /= 10;
		if(b==7){
			count++;
		}
	}
	return count;
}

int main()
{
	int a;
	scanf("%d",&a);
	int count = fun(a);
	printf("7的个数为:%d\n",count);
	return 0;
}