#include<stdio.h>
#define MAX_NUM 0x100
int main()
{
	char str[MAX_NUM];
	char value;
	int count;
	printf("分别输入一个字符，和一个自然数\n");
	scanf("%c%d",&value,&count);

	_asm{
		LEA EDI, str
		XOR ECX, ECX
		MOV BL, value
		MOV EAX, count
	CIRCLE:
	    MOV [EDI], BL
		INC ECX
		INC EDI
		CMP ECX, EAX
		JL CIRCLE
		MOV [EDI],0
	}
	printf("%s\n",str);
	return 0;
}