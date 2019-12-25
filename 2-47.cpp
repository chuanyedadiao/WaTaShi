#include<stdio.h>

int main()
{
	char buff[256];
	char str[256];
	char str2[256];
	scanf("%s",buff);
	_asm{
		LEA EAX, buff
		PUSH EAX
		CALL STRLEN
		POP ECX 
		LEA ECX, buff
		PUSH EAX
		PUSH ECX
		CALL TRANCE 
		POP ECX
		POP EBX

		LEA EDI, str 
		MOV EBX, 16
    circle:
		MOV EDX, 0
		IDIV EBX
		CMP EDX, 0
		JZ LAB1
		JMP LAB2
    LAB1:
		CMP EAX, 0
		JZ LABOUT
    LAB2:
		CMP EDX, 10
		JL LAB3
		JMP LAB4
    LAB3:
		ADD EDX, 30H
		MOV [EDI], EDX
		INC EDI
		JMP circle
    LAB4:
		ADD EDX, 37H
		MOV [EDI], EDX
		INC EDI
		JMP circle
    LABOUT:
		LEA ESI, str
		LEA EDI, str2
		MOV ECX, 0
    circle1:
		CMP [ESI+ECX], 0
		JZ LAB5
		INC ECX
		JMP circle1
    LAB5:
		MOV EDX, ECX
		DEC EDX
	LAB6:
		MOV AL, [ESI+EDX]
		DEC EDX
		MOV [EDI], AL
		INC EDI
		CMP EDX, 0
		JGE LAB6
		MOV AL, 0
		MOV [EDI], AL
	}
	printf("%s\n",str2);
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
	_asm{
	TRANCE:
	    PUSH EBP
		MOV EBP, ESP
		PUSH EDI
		PUSH ESI
		MOV EDI, [EBP+8]
		MOV ESI, [EBP+12]
		MOV EAX, 0
		MOV ECX, 0
		ADD EDI, ESI
		DEC EDI

    LTHREE:
		MOV EDX, ECX
		MOV EBX, 1
	LTWO:
		CMP ECX, 1
		JL LONE
		DEC ECX
		IMUL EBX, 10
		JMP LTWO
    LONE:
		MOV ECX, EDX
		MOV DL, [EDI]
		AND EDX, 000000ffH
		SUB DL, 30H
		IMUL EDX, EBX
		ADD EAX, EDX
		DEC EDI
		INC ECX
		CMP ECX, ESI
		JL LTHREE

		POP ESI
		POP EDI
		POP EBP
		RET
	}
}