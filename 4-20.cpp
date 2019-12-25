#include<stdio.h>

int main()
{
	char str1[0x100],str2[0x100];
	scanf("%s",str1);
	scanf("%s",str2);
	int local=-1;
	_asm{
		LEA EAX, str1
		PUSH EAX
		CALL STRLEN
		POP ECX
		MOV EBX, EAX
		
		LEA EAX, str2
		PUSH EAX
		CALL STRLEN
		POP ECX
		;
		XOR ECX, ECX
		LEA ESI, str1
		LEA EDI, str2
    CIRCLE:
		MOV DL, [ESI]
		PUSH ECX
		PUSH EBX
		XOR ECX, ECX
    LAB1:
		MOV BL, [EDI+ECX]
		CMP BL, DL
		JE LABOUT1
		INC ECX
		CMP ECX, EAX
		JL LAB1
		POP EBX
		POP ECX
		INC ECX
		INC ESI
		CMP ECX, EBX
		JL CIRCLE
		JMP LABOUT2
    LABOUT1:
		POP EBX
		POP ECX
		INC ECX
		MOV local, ECX
		JMP LABOUT
    LABOUT2:
		MOV EAX, -1
	    MOV local, EAX
	LABOUT:
	    
	}
	printf("%d\n",local);
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