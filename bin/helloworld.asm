Length  dw  End     ; 工作程序的长度
Start   dw  Begin   ; 工作程序入口的偏移
Zoneseg dw  0900H   ; 期望内存区域的起始段值
Reserved dd 0       ; 保留

hello db "Hello, world", 0DH, 0AH, 0

Begin:
    cld
    push cs
    pop ds
    mov si, hello
Lab1:
    lodsb ; 将si指向的一个字节，装入al中
    or al, al
    jz Lab2
    mov ah, 14
    int 10H 
    jmp short Lab1
Lab2:
    retf

End:

;在2号扇区