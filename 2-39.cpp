#include<stdio.h>

int main()
{
	char str[256];
	char str2[256];
	scanf("%s",str);
	int n;
	_asm{
		LEA ESI, str
		LEA EDI, str2
		MOV ECX, 0
    circle1:
		CMP [ESI+ECX], 0
		JZ lab1
		INC ECX
		JMP circle1
    lab1:
		MOV EDX, ECX
		DEC EDX
	lab2:
		MOV AL, [ESI+EDX]
		DEC EDX
		MOV [EDI], AL
		INC EDI
		CMP EDX, 0
		JGE lab2
		MOV AL, 0
		MOV [EDI], AL
	}
	printf("%s\n",str2);
	return 0;
}