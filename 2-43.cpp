/*#include<stdio.h>

char buff[256];
char str[256];
char str2[256];


int main()
{
	scanf("%s",buff);
	_asm{
	STRLEN:
		LEA EDI,buff
		XOR AL, AL
		MOV ECX, -1
		REPNZ SCASB
		NOT ECX
		DEC ECX
		MOV EAX, ECX
		;
    lab2:
		LEA EDI,str
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
		MOV [EDI],EDX
		INC EDI
		JMP CIRCLE
    labout:
		MOV [EDI], 0

		LEA ESI, str
		LEA EDI, str2
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
	}
	printf("%s\n",str2);
	return 0;
 
return 0;
}*/
#include<stdio.h>
 
int gcd(int a,int b);
int lcm(int a,int b);
int main(void)
{
int m,n,result_gcd,result_lcm;
 
printf("求两个数的最大公约数及最小公倍数？\n请输入你想计算的两个数：\n");
scanf("%d%d",&m,&n);
result_gcd=gcd(m,n);
result_lcm=lcm(m,n);
printf("最大公约数为：%d\n最小公倍数为：%d\n",result_gcd,result_lcm);
 
return 0;
}
 
int gcd(int a,int b)
{
int temp;
if(a<b)
{
//交换两个数，使大数放在a上
temp=a;
a=b;
b=temp;
}
while(b!=0)
{
//利用辗除法，直到b为0为止
temp=a%b;
a=b;
b=temp;
}
return a;
}
 
 
int lcm(int a,int b)
{
int temp_lcm;
temp_lcm=a*b/gcd(a,b);//最小公倍数等于两数之积除以其最大公约数
return temp_lcm;
}