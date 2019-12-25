#include<stdio.h>

int main()
{
	int a1,a2;
	int temp1,temp2;
	printf("输入两个数值:\n");
	scanf("%d%d",&a1,&a2);
	_asm{
		MOV EAX, a1
		MOV ECX, a2
		;
		CMP EAX, ECX
		JG NEXT1
		MOV temp1, ECX
		JMP LAB1
    NEXT1:
        MOV temp1, EAX
		;
	LAB1:
		CMP EAX, ECX
        JA NEXT2
		MOV temp2, ECX
		JMP LAB2
    NEXT2:
		MOV temp2, EAX
		;
	LAB2:
	}
	printf("有符号数比较，较大者是: %d\n",temp1);
	printf("无符号数比较，较大者是: %d\n",temp2);
}