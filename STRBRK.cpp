#include<stdio.h>
#define MAX_NUM 0X100
int main()
{
	char str[MAX_NUM],control[MAX_NUM];
	scanf("%s%s",str,control);
	int n,i;
	char *p = NULL;
	//printf("%s\n%s\n",str,control);

	_asm{
		LEA ESI, str
		LEA EDI, control
		PUSH ESI
		CALL STRLEN
		POP ESI
		MOV n, EAX
		;
		PUSH EDI
		CALL STRLEN
		POP EDI
		MOV EDX, EAX
		;

		XOR ECX, ECX
	LAB_1:	
	    MOV BL, [ESI]
		MOV i, ECX
		PUSH BL
		PUSH EDX
		PUSH EDI
		CALL FIND
		POP EDI
		POP EDX
		POP EBX
		CMP EAX, 1
		JZ LAB_OUT1
		MOV ECX, i
		MOV EBX, n
		INC ECX
		INC ESI
		CMP ECX, EBX
		JL LAB_1
		JMP LAB_OUT2
	LAB_OUT1:
	    MOV p, ESI
	LAB_OUT2:
	}
	if(p==NULL) printf("无相同字符，P为空指针\n");
	else printf("指针为:%x\n指针的值为:%c\n",p,*p);

	return 0;
	_asm{
	STRLEN:
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, [EBP+8]
		XOR ECX, ECX
	CIRCLE:
	    MOV BL, [EAX]
		CMP BL, 0
        JZ LABOUT
		INC ECX
		INC EAX
		JMP CIRCLE
    LABOUT:
		MOV EAX, ECX
		POP EBP
		RET
	}
	_asm{
	FIND:
	    PUSH EBP
		MOV EBP, ESP
		PUSH EDI
		MOV EDI, [EBP+8]
		MOV EDX, [EBP+12]
		MOV AL, [EBP+16]
		XOR ECX, ECX
	FIND_LAB1:
	    MOV BL, [EDI]
		CMP AL, BL
		JZ FIND_LABOUT1
		INC ECX
		INC EDI
		CMP ECX, EDX
		JL FIND_LAB1
		MOV EAX, 0
		JMP FIND_LABOUT2
    FIND_LABOUT1:
        MOV EAX, 1
	FIND_LABOUT2:
	    POP EDI
		POP EBP
		RET
	}
}