#include<stdio.h>

int main()
{
	int a1,a2;
	int temp1,temp2;
	printf("����������ֵ:\n");
	scanf("%d%d",&a1,&a2);
	_asm{
		MOV EAX, a1
		MOV ECX, a2
		;
		CMP EAX, ECX
		JG NEXT1
		MOV temp1, ECX
		JMP LAB1
    NEXT1:
        MOV temp1, EAX
		;
	LAB1:
		CMP EAX, ECX
        JA NEXT2
		MOV temp2, ECX
		JMP LAB2
    NEXT2:
		MOV temp2, EAX
		;
	LAB2:
	}
	printf("�з������Ƚϣ��ϴ�����: %d\n",temp1);
	printf("�޷������Ƚϣ��ϴ�����: %d\n",temp2);
}