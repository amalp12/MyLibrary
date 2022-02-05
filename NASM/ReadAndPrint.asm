section .data
    message : db "Please Enter Your Name: ",10
    message_length: equ $-message

section .bss
    name : resb 1
    name_length : resb 1

section .text
    global _start:
    _start:
        mov eax, 4
        mov ebx , 1
        mov ecx , message
        mov edx, message_length
        int 80h


        mov eax, 3; Syscall number for Read
        mov ebx, 0; Source is set to keyboard
        mov ecx, name; input is read into the pointer 'name'
        mov edx, name_length; Length of the input
        int 80h; Call the Syscall


        mov eax, 4; Syscall number for Write
        mov ebx, 1 
        mov ecx, name;
        mov edx, name_length;
        int 80h; Call the Syscall

        mov eax, 1
        mov ebx, 0
        int 80h



