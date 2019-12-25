#include<stdio.h>

int main()
{
	int a[256],b[256];
	scanf("%s%s",a,b);
	char str1[256]={'0'},str2[256]={'0'},str3[256]={'0'},str4[256]={'0'};
	_asm{
		LEA EAX, a
		PUSH EAX
		CALL STRLEN
		POP ECX 
		LEA ECX, a
		PUSH EAX
		PUSH ECX
		CALL TRANCE1 
		POP ECX
		POP EBX
		PUSH EAX
		;

		LEA EAX, b
		PUSH EAX
		CALL STRLEN
		POP ECX 
		LEA ECX, b
		PUSH EAX
		PUSH ECX
		CALL TRANCE1 
		POP ECX
		POP EBX
		POP EBX
		MOV ECX, EAX
		;

		PUSH EBX
		PUSH ECX
		CALL CAL_Quotient
		POP ECX
		POP EBX
		PUSH EDX
		CMP EAX, 0
		JZ ONE_D
		LEA EBX, str1
		LEA ECX, str2
		PUSH EAX
		PUSH EBX
		PUSH ECX
		CALL TRANCE
		POP ECX
		POP EBX
		POP EAX
    ONE_D:
		POP EDX
		CMP EDX, 0
		JZ ONE_OUT
		MOV EAX, EDX
		LEA EBX, str3
		LEA ECX, str4
		PUSH EAX
		PUSH EBX
		PUSH ECX
		CALL TRANCE
		POP ECX
		POP EBX
		POP EAX
	ONE_OUT:
	}
	printf("ษฬ:%s ,ำเสý:%s\n",str2,str4);
	return 0;
	_asm{
    CAL_Quotient:
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+12]
		MOV ECX, [EBP+8]
		MOV EDX, 0
		IDIV ECX
		POP EBP
		RET
	}
	_asm{
    TRANCE:
		PUSH EBP
		MOV EBP, ESP
		PUSH ESI
		PUSH EDI
		MOV ESI, [EBP+12] 
		MOV EDI, [EBP+8]  
		MOV EAX, [EBP+16]
	lab2:
		MOV EBX, 10
    CIRCLE:
		MOV EDX, 0
		IDIV EBX
		CMP EDX, 0
		JZ lab3
		JMP lab4
	lab3:
		CMP EAX, 0
		JZ labout
		;
	lab4:
		ADD EDX,30H
		MOV [ESI],EDX
		INC ESI
		JMP CIRCLE
    labout:
		MOV [ESI], 0

		MOV ESI, [EBP+12]
		MOV ECX, 0
    circle1:
		CMP [ESI+ECX], 0
		JZ lab5
		INC ECX
		JMP circle1
    lab5:
		MOV EDX, ECX
		DEC EDX
	lab6:
		MOV AL, [ESI+EDX]
		DEC EDX
		MOV [EDI], AL
		INC EDI
		CMP EDX, 0
		JGE lab6
		MOV AL, 0
		MOV [EDI], AL

		POP EDI
		POP ESI
		POP EBP
		RET
	}
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
	TRANCE1:
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