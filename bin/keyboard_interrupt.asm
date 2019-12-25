PORT_KEY_DAT equ 0x60
PORT_KEY_STA equ 0x64
;
section text
bits 16

Length  dw  End     ; 工作程序的长度
Start   dw  Begin   ; 工作程序入口的偏移
Zoneseg dw  1500H   ; 期望内存区域的起始段值
Reserved dd 0       
;-----------------------------------------
Begin:
    mov ax,0
    mov ds,ax
    cli
    mov word[9*4],int09h_handler
    mov [9*4+2],cs
    sti
    ;
Next:
    mov ah,0
    int 16H
    ;
    mov ah,14
    int 10H
    ;
    cmp al,0dH
    jnz Next
    ;
    mov ah,14
    mov al,0aH
    int 10H
    ;
    retf
int09h_handler:
    pusha
    ;
    mov al,0adH
    out PORT_KEY_STA,al
    ;
    in al,PORT_KEY_DAT
    ;
    sti
    call int09hfun
    ;
    cli
    mov al,0aeH
    out PORT_KEY_STA, al
    ;
    mov al,20H
    out 20H,al
    ;
    popa
    ;
    iret
;---------------------------------------------
int09hfun:
    cmp al,1cH
    jnz .LAB1
    mov ah,al
    mov al,0dH
    jmp short .LAB2
.LAB1:
    cmp al,10H
    jb .LAB3
    cmp al,19H
    ja .LAB3
    mov ah,al
    add al,20H
.LAB2:
    call Enqueue
.LAB3:
    ret
;---------------------------------------------
Enqueue:
    push ds
    mov bx,40H
    mov ds,bx
    mov bx,[001CH]
    mov si,bx
    add si,2
    cmp si,003eH
    jb .LAB1
    mov si, 001eH
.LAB1:
    cmp si,[001aH]
    jz .LAB2
    mov [bx],ax
    mov [001cH],si
.LAB2:
    pop ds
    ret
End:

;放在10号扇区
;识别QWERTYUIOP和回车 0123456789 回车就终止