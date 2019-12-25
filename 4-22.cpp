#include<stdio.h>

int main()
{
	int n;
	scanf("%d",&n);
	getchar();
	char ch;
	scanf("%c",&ch);
	char str[0x100];
	
	//mov         cl,byte ptr [ebp-15h]
	_asm{
		LEA EAX, str
		MOV EDX, n
		MOV BL, byte ptr [ebp-15h]
		PUSH BL
		PUSH EAX
		PUSH EDX
		CALL EXTEND
		POP EDX
		POP ECX
		POP BL
	}
	printf("%s\n",str);
	return 0;
	_asm{
	EXTEND:
		PUSH EBP
		MOV EBP, ESP
		MOV BL, [EBP+16]
		MOV EAX, [EBP+12]
		MOV EDX, [EBP+8]
		XOR ECX, ECX
    CIRCLE:
		MOV [EAX], BL
		INC ECX
		INC EAX
		CMP ECX, EDX
		JL CIRCLE
		MOV [EAX], 0

		POP EBP
		RET
	}
}