#include<stdio.h>
#include<string.h>
#define MAX_NUM 0x100

int sumOfnumber(char str[])
{
	int count=0;
	int n = strlen(str);
	int i;
	for(i=0;i<n;i++){
		if(str[i]>=0x30&&str[i]<=0x39)
			count++;
	}
	return count;
}

int sumOfLetter(char str[])
{
	int count=0;
	int n = strlen(str);
	int i;
	for(i=0;i<n;i++){
		if((str[i]>=0x41&&str[i]<=0x5A) || (str[i]>=0x61&&str[i]<=0x7A))
			count++;
	}
	return count;
}

void sum(char str[],int *a,int *b)
{
	*a = sumOfLetter(str);
	*b = sumOfnumber(str);
}

int main()
{
    char str[MAX_NUM];
	scanf("%s",str);
	int letter=0,number=0;
	sum(str,&letter,&number);
	printf("×ÖÄ¸ÓĞ:%d Êı×ÖÓĞ:%d\n",letter,number);
	return 0;
}