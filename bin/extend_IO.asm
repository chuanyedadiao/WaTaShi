section text
bits 16

Length  dw  End     ; 工作程序的长度
Start   dw  Begin   ; 工作程序入口的偏移
Zoneseg dw  1A00H   ; 期望内存区域的起始段值
Reserved dd 0 

;---------------------------------
newhandler:
    sti
    pusha
    push ds
    push es
    ;
    call PutChar
    ;
    pop es
    pop ds
    popa
    iret
;-----------------------------------
PutChar:
    push ax
    mov ax,0B800H
    mov ds,ax
    mov es,ax
    pop ax
    ;
    call get_lcursor
    ;
    cmp al,0dH
    jnz .Lab1
    mov dl,0
    jmp .Lab3
.Lab1:
    cmp al,0aH
    jz .Lab2
    ;
    mov ah,bl
    mov bx,0
    mov bl,dh
    imul bx,80
    add bl,dl
    adc bh,0
    shl bx,1
    ;
    mov [bx],ax
    ;
    inc dl
    cmp al,80
    jb .Lab3
    mov dl,0
.Lab2:
    inc dh
    cmp dh,25
    jb .Lab3
    dec dh
    cld
    mov si,80*2
    mov es,ax
    mov di,0
    mov cx,80*24
    rep movsw
    ;
    mov cx,80
    mov di,80*24*2
    mov ax,0x720
    rep stosw
.Lab3:
    call set_lcursor
    call set_pcursor
    ret
;--------------------------------
get_lcursor:
    push ds
    push 0040H
    pop ds
    mov dl,[0050H]
    mov dh,[0051H]
    pop ds
    ret
;---------------------------------
set_lcursor:
    push ds
    push 0040H
    pop ds
    mov [0050H],dl
    mov [0051H],dh
    pop ds
    ret
;---------------------------------
set_pcursor:
    mov al,80
    mul dh
    add al,dl
    adc ah,0
    mov cx,ax
    ;
    mov dx,3d4H
    mov al,14
    out dx,al
    mov dx,3d5H
    mov al,ch
    out dx,al
    ;
    mov dx,3d4H
    mov al,15
    out dx,al
    mov dx,3d5H
    mov al,cl
    out dx,al
    ret

;====================================
Begin:
    mov al,0
    mov ah,5
    int 10h
    ;
    xor ax,ax
    mov ds,ax
    cli
    mov word[90H*4],newhandler
    mov [90H*4+2],cs
    sti
    ;
    push cs
    pop ds
    cld
    mov si,mess
    mov bl,17H
.Lab1:
    lodsb
    or al,al
    jz .Lab2
    ;
    int 90H
    ;
    jmp .Lab1
.Lab2:
    retf
    ;
mess db "No.90H handler is ready.",0dh,0ah,0
End:

;放在20