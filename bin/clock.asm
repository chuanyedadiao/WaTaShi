section text
bits 16

Length  dw  End     ; 工作程序的长度
Start   dw  Begin   ; 工作程序入口的偏移
Zoneseg dw  2800H   ; 期望内存区域的起始段值
Reserved dd 0       
;-----------------------------------------
Entry_1CH:
    dec byte [cs:count]
    jz ETIME
    iret
    ;
ETIME:
    mov byte [cs:count],18
    sti
    pusha
    call get_time
    call EchoTime
    popa
    iret
;------------------------------------------
get_time:
    mov al,4
    out 70H,al
    in al,71H
    mov ch,al
    mov al,2
    out 70h,al
    in al,71h
    mov cl,al
    mov al,0
    out 70h,al
    in al,71h
    mov dh,al
    ret
;-----------------------------------------
%define ROW 10
%define COLUMN 36
EchoTime:
    push si
    ;--------
    push dx
    push cx
    mov bh,0
    mov ah,3
    int 10h
    mov si,dx
    mov dx,(ROW<<8)+COLUMN
    mov ah,2
    int 10h
    pop cx
    pop dx
    ;--------
    mov al,ch
    call EchoBCD
    mov al,':'
    call PutChar
    mov al,cl
    call EchoBCD
    mov al,':'
    call PutChar
    mov al,dh
    call EchoBCD
    ;---------
    mov dx,si
    mov ah,2
    int 10h
    pop si
    ret
;--------------------------------------------
EchoBCD:
  push ax
  shr al,4
  add al,'0'
  call PutChar
  pop ax
  and al,0FH
  add al,'0'
  call PutChar
  ret
PutChar:
  mov bh,0
  mov ah,14
  int 10H
  ret  
;------------------------------------------
count db 1
old1ch dd 0
;-----------------------------------------
Begin:
  mov ax,cs
  mov ds,ax
  mov si,1cH*4
  mov ax,0
  mov es,ax
  ;
  mov ax,[es:si]
  mov [old1ch],ax
  mov ax,[es:si+2]
  mov [old1ch+2],ax
  ;
  cli
  mov ax,Entry_1CH
  mov [es:si],ax
  mov ax,cs
  mov [es:si+2],ax
  sti
;-------------------------------------------
Continue:
  mov ah,0
  int 16h
  ;
  cmp al,20h
  jb Continue
  call PutChar
  ;
  cmp al,'#'
  jnz Continue
  ;-----------------------------
  mov eax,[cs:old1ch]
  mov [es:si],eax
  ;
  retf
End:
;clock在28扇区