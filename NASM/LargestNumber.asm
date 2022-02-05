
section .data
    message1: db 'Enter First Number :', 10
    message1_length: equ $ - message1

    message2: db 'Enter Second Number :', 10
    message2_length: equ $ - message2

    messageEqual: db 'Both Numbers are Equal with Value :', 10
    messageEqual_length: equ $ - messageEqual

    messageFirstIsGreater : db 'First Number is Greater with Value :', 10
    messageFirstIsGreater_length: equ $ - messageFirstIsGreater

    messageSecondIsGreater : db 'Second Number is Greater with Value :', 10
    messageSecondIsGreater_length: equ $ - messageSecondIsGreater


section .bss
    input_buffer : resb 1
    number_1: resb 1
    number_2: resb 1




section .text
global _start:
    _start:

    ; printing message1
    mov eax , 4
    mov ebx , 1
    mov ecx , message1
    mov edx , message1_length
    int 80h

    ; Taking first number input
    mov eax, 3
    mov ebx, 0
    mov ecx, number_1;
    mov edx, 1;
    int 80h
   

    ; Taking junk input
    mov eax, 3
    mov ebx, 0
    mov ecx, input_buffer;
    mov edx, 1;
    int 80h

    ; printing message2
    mov eax , 4
    mov ebx , 1
    mov ecx , message2
    mov edx , message2_length
    int 80h


    ; Taking Second number input
    mov eax, 3
    mov ebx, 0
    mov ecx, number_2;
    mov edx, 1;
    int 80h

    ; converting both numbers from ascci to integer
    sub byte[number_1], 30h
    sub byte[number_2], 30h

    ; comparing both numbers
    mov al , byte[number_1]
    cmp al , byte[number_2]
    ja number_1_greater
    jb number_2_greater
    je numbers_equal


    number_1_greater:
        ; printing greater message
        mov eax , 4
        mov ebx , 1
        mov ecx , messageFirstIsGreater
        mov edx , messageFirstIsGreater_length
        int 80h

        ; printing number_1
        add byte[number_1], 30h
        mov eax , 4
        mov ebx , 1
        mov ecx , number_1
        mov edx , 1
        int 80h

        jmp Exit

    number_2_greater:

        ; printing greater message
        mov eax , 4
        mov ebx , 1
        mov ecx , messageSecondIsGreater
        mov edx , messageSecondIsGreater_length
        int 80h

        ; printing number_2
        add byte[number_2], 30h
        mov eax , 4
        mov ebx , 1
        mov ecx , number_2
        mov edx , 1
        int 80h

        jmp Exit

    numbers_equal:
        ; printing equal message
        mov eax , 4
        mov ebx , 1
        mov ecx , messageEqual
        mov edx , messageEqual_length
        int 80h

        ; printing number_1
        add byte[number_1], 30h
        mov eax , 4
        mov ebx , 1
        mov ecx , number_1
        mov edx , 1
        int 80h

        jmp Exit


    Exit:
        ; printing new line
        mov eax, 4
        mov ebx, 1
        mov ecx, 10
        mov edx, 1
        int 80h



        ; exit call
        mov eax , 1
        mov ebx , 0
        int 80h
