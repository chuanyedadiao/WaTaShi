#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char *str;
	str = (char*)malloc(256*sizeof(char));
	scanf("%s",str);
	int count;
	_asm{
		MOV EBX, str
		MOV ECX, 0
    LAB1:
		MOV DL, [EBX+ECX]
		INC ECX
		CMP DL, 0
		JNZ LAB1
		DEC ECX
		MOV count, ECX
	}
	printf("%d\n",count);
	return 0;
}