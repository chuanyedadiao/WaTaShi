#include<stdio.h>
#define MAX_NUM 0X100
int main()
{
    char str[MAX_NUM];
	scanf("%s",str);
	int count=0;
	_asm{
		LEA EAX, str
		XOR ECX, ECX
	CIRCLE:
	    MOV BL, [EAX]
		CMP BL, 0
        JZ LABOUT
		INC ECX
		INC EAX
		JMP CIRCLE
    LABOUT:
		MOV count, ECX
	}
	printf("%d\n",count);
	return 0;
}