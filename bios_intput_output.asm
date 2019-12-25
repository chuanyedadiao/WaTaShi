Length  dw  End     ; 工作程序的长度
Start   dw  Begin   ; 工作程序入口的偏移
Zoneseg dw  0900H   ; 期望内存区域的起始段值
Reserved dd 0

section text
bits 16
%define space 20H
%define enter 0dH
%define newline 0aH
%define backspace 08H
%define bell 07H
%define lenebuf 16
;

Begin:
    cld
    push cs
    pop ds
    mov dx,buffer
    call GetDStr
    ;
    mov al,enter
    call PutChar
    mov al,newline
    call PutChar
    ;
    mov dx,buffer+1
    call PutDStr
    ;
    retf
    ;
buffer:
    db lenebuf
    resb lenebuf
;--------------------------------

GetDStr:
    push si
    mov si,dx
    cmp cl,1
    jb .Lab6
    ;
    inc si
    xor ch,ch
.Lab1:
    call GetChar
    or al,al
    jz short .Lab1
    cmp al,enter
    jz short .Lab5
    cmp al,backspace
    jz short .Lab4
    cmp al,space
    jb short .Lab1
    ;
    cmp al,'0'
    jb short .Lab1
    cmp al,'9'
    ja short .Lab1
    ;
    cmp cl,1
    ja short .Lab3
.Lab2:
    mov al,bell
    call PutChar
    jmp short .Lab1
.Lab3:
    call PutChar
    mov [si],al
    inc si
    inc ch
    dec cl
    jmp short .Lab1
    ;
.Lab4:
    cmp ch,0
    jbe .Lab2
    call PutChar
    mov al,space
    call PutChar
    mov al,backspace
    call PutChar
    dec si
    dec ch
    inc cl
    jmp short .Lab1
    ;
.Lab5:
    mov [si],al
.Lab6:
    pop si
    ret
;----------------------------
PutDStr:
    push si
    mov si,dx
.Lab1:
    lodsb
    call PutChar
    cmp al,enter
    jnz .Lab1
    mov al,newline
    call PutChar
    pop si
    ret
;----------------------------
PutChar:
    mov bh,0
    mov ah,14
    int 10H
    ret
;---------------------------
GetChar:
    mov ah,0
    int 16h
    ret
End:
;放在36