#include<stdio.h>

int main()
{
	unsigned int a;
	int count;
	scanf("%u",&a);
	_asm{
		MOV EBX, a
		MOV ECX, 0
		MOV ESI, 0
	circle:
		MOV EDX, EBX
		AND EDX, 1
		CMP EDX, 0
		JNZ LAB1
		INC ESI
    LAB1:
        SHR EBX, 1
		INC ECX
		CMP ECX, 32
		JZ LAB2
		JMP circle
    LAB2:
		MOV count,ESI
	}
	printf("%d\n",count);
	return 0;
}