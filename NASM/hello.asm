section .data
    var1 : db 'Hello',10
    len: equ $-var1

section .text
global _start:  
    _start:
    mov eax, 4
    mov ebx, 1
    mov ecx, var1
    mov edx, len ; length
    int 80h

	mov eax, 1
	mov ebx, 0
	int 80h