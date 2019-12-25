#include<stdio.h>

char buff[]="ABCDE196384";

int main()
{
	short int result1,result2;
	_asm{
		LEA EBX,buff
		MOV ECX, 0
		MOV AX, 0
		;
    circle:
		MOV DL,[EBX+ECX]
		CMP DL,0
		JZ lab3
		CMP DL,41H
		JB lab2
		JMP lab1
    lab1:
		SUB DL,37H
		ADD AL,DL
		INC ECX
		JMP circle
    lab2:
		SUB DL,30H
		ADD AL,DL
		INC ECX
		JMP circle
    lab3:
		MOV result1, AX
	}
	printf("%d\n",result1);
}