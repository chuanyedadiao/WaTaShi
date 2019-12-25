Length  dw  End     ; 工作程序的长度
Start   dw  Begin   ; 工作程序入口的偏移
Zoneseg dw  1800H   ; 期望内存区域的起始段值
Reserved dd 0 

Begin:
    mov ax,0
    mov ds,ax
    cli
    mov word[0*4],int00h_handler
    mov [0*4+2],cs
    sti
    ;
    mov bh,0
    mov ah,14
    mov al,'#'
    int 10H
    ;
    mov ax,600
    mov bl,2
    div bl
LABV:
    ;
    mov ah,14
    mov al,0dH
    int 10H
    mov al,0aH
    int 10H
    ;
    retf

;-------------------------------------
int00h_handler:
    sti
    pusha
    push ds
    mov bp,sp
    ;
    push cs
    pop ds
    mov dx,mess
    call PutStr
    ;
    add word[bp+18],2
    ;
    pop ds
    popa
    ;
    iret
    ;
mess db "Divide overflow",0
;
PutStr:
    mov bh,0
    mov si,dx
.LAB1:
    lodsb
    or al,al
    jz .LAB2
    mov ah,14
    int 10H
    jmp .LAB1
.LAB2:
    ret
End: 
;放在17