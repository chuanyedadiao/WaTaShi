#include<stdio.h>

int main()
{
	char str1[0x100];
	scanf("%s",str1);
	char str2[20]={0x21,0x22,0x27,0X2c,0x2e,0x2f,0x3a,0x3b,0x3f,0x5f};
	char str3[0x100];
	int n;
	_asm{
		LEA EAX, str1
		PUSH EAX
		CALL STRLEN
		POP EBX
		MOV n, EAX
		;
		XOR ECX, ECX

		LEA ESI, str1
		LEA EDI, str3
    CIRCLE:
	    LEA EBX, str2
		PUSH ESI
		PUSH EBX
		PUSH ECX
		CALL JUDGE
		POP ECX
		POP EBX
		POP ESI
		CMP EAX, 0
		JZ LAB_1
		JMP LAB_2
	LAB_1:
		MOV BL, [ESI+ECX]
		MOV [EDI], BL
		INC EDI
	LAB_2:
	    INC ECX
		MOV EDX, n
		CMP ECX, EDX
		JL CIRCLE
		MOV [EDI], 0
	}
	printf("%s\n",str3);
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
	JUDGE:
	    PUSH EBP
		MOV EBP, ESP
		PUSH ESI
		PUSH EDI
		MOV ECX, [EBP+8]
		MOV EDI, [EBP+12] //STR2
		MOV ESI, [EBP+16] //STR1
		MOV EBX, 0
		MOV DL, [ESI+ECX]
	JUDGE_LAB:
		MOV AL, [EDI+EBX]
		CMP DL, AL
		JZ JUDGE_OUT1
		INC EBX
		CMP EBX, 10
		JL JUDGE_LAB
		JMP JUDGE_OUT2
    JUDGE_OUT1:
		MOV EAX, 1
		JMP JUDGE_OUT
    JUDGE_OUT2:
		XOR EAX,EAX
	JUDGE_OUT:
	    POP EDI
		POP ESI
		POP EBP
		RET
	}
}