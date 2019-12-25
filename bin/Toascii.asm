;在30号扇区


Length  dw  End     ; 工作程序的长度
Start   dw  Begin   ; 工作程序入口的偏移
Zoneseg dw  0900H   ; 期望内存区域的起始段值
Reserved dd 0       ; 保留

pressInfor db "Press a key", 0DH, 0AH, 0

Begin:
    cld
    push cs
    pop ds
    mov si, pressInfor
    call Lab1
    call GetChar
    mov bl,al
    shr al,4
    call TOASCII
    mov [result],al
    mov al,bl
    call TOASCII
    mov [result+1],al
    ;
    mov si, result
    call Lab1
    ;
    retf
GetChar:
    mov ah,0
    int 16h
    ret

Lab1:
    lodsb ; 将si指向的一个字节，装入al中
    or al, al
    jz Lab2
    mov ah, 14
    int 10H 
    jmp short Lab1
Lab2:
    ret

TOASCII:
    and al,0fH
    add al,'0'
    cmp al,'9'
    jbe Lab3
    add al,7
Lab3:
    ret
;--------------------------------
mess0 db 'Press a key',0DH,0AH,0
result db 0,0
       db 'H',0
End: