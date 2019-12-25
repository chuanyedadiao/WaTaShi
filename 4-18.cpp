#include<stdio.h>

int main()
{
	char str1[0x100],str2[0x100];
	scanf("%s",str1);
	scanf("%s",str2);
	_asm{
		LEA EAX,str1
		PUSH EAX
		CALL STRLEN
		POP EBX
		MOV EBX, EAX
		LEA EDX,str2
		PUSH EDX
		CALL STRLEN
		POP EDX

		XOR ECX, ECX
		LEA ESI, str1
		LEA EDX, str2
		ADD ESI, EBX
	CIRCLE:
		MOV BL, [EDX]
		MOV [ESI], BL
		INC ESI
		INC EDX
		INC ECX
		CMP ECX, EAX
		JL CIRCLE
		XOR BL, BL
		MOV [ESI], BL
	}
	printf("%s\n",str1);
	return 0;
	_asm{
	STRLEN:
		PUSH EBP
		MOV EBP, ESP
		PUSH EDI
		MOV EDI, [EBP+8]
		XOR AL, AL
		MOV ECX, -1
		REPNZ SCASB
		NOT ECX
		DEC ECX
		MOV EAX, ECX
		POP EDI
		POP EBP
		RET
	}
}