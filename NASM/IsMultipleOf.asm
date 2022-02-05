
section .data
    message1: db 'Enter First Number ', 10
    message1_length: equ $ - message1

    message2: db 'Enter Second Number ', 10
    message2_length: equ $ - message2

    is_multiple : db ' is a Multiple of '
    is_multiple_length : equ $ - is_multiple

    not_multiple : db ' is not a Multiple of '
    not_multiple_length : equ $ - not_multiple





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


        ; Taking second number input
        mov eax, 3
        mov ebx, 0
        mov ecx, number_2;
        mov edx, 1;
        int 80h

        ; Taking junk input
        mov eax, 3
        mov ebx, 0
        mov ecx, input_buffer;
        mov edx, 1;
        int 80h




        ; converting both numbers from ascci to integer
        sub byte[number_1], 30h ; a
        sub byte[number_2], 30h ; b
    

        ; (b%a==0)
        mov ax , word[number_2]
        mov bl , byte[number_1]
        mov ah, 0
        div bl ; divides ax by bl (or somenumber) and puts the quotient in al and the remainder in ah. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".

        ; converting both numbers from integer to ascci
        add byte[number_1], 30h ; a
        add byte[number_2], 30h ; b

        ; ah will have the reminder
        cmp ah,0;

        je IsMultiple
        jne NotMultiple

        IsMultiple:
            ; printing first number
            mov eax, 4
            mov ebx, 1
            mov ecx, number_1
            mov edx, 1
            int 80h

            ; printing is a Multiple message
            mov eax, 4
            mov ebx, 1
            mov ecx, is_multiple
            mov edx, is_multiple_length
            int 80h

            ; printing second number
            mov eax, 4
            mov ebx, 1
            mov ecx, number_2
            mov edx, 1
            int 80h

            jmp Exit
            
        NotMultiple :
            ; printing first number
            mov eax, 4
            mov ebx, 1
            mov ecx, number_1
            mov edx, 1
            int 80h

            ; printing is not a Multiple message
            mov eax, 4
            mov ebx, 1
            mov ecx, not_multiple
            mov edx, not_multiple_length
            int 80h

            ; printing second number
            mov eax, 4
            mov ebx, 1
            mov ecx, number_2
            mov edx, 1
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
