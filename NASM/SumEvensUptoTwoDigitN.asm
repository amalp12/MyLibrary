
section .data
    message1: db 'Enter First Digit ', 10
    message1_length: equ $ - message1

    message2: db 'Enter Second Digit ', 10
    message2_length: equ $ - message2




section .bss
    input_buffer : resb 1
    number_1: resw 1
    number_2: resw 1
    number: resw 1

    counter: resw 1
    sum : resw 1

    temp: resw 1
    carry: resb 1
    ones_answer: resw 1
    tens_answer: resw 1
    hundreds_answer: resw 1
    thousands_answer: resw 1



section .text
    global _start:
        _start:

        ; printing message1
        mov eax , 4
        mov ebx , 1
        mov ecx , message1
        mov edx , message1_length
        int 80h

        ; Taking first digit input
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


        ; Taking  second digit input
        mov eax, 3
        mov ebx, 0
        mov ecx, number_2;
        mov edx, 1;
        int 80h

        




        ; converting both numbers from ascci to integer
        sub word[number_1], 30h ; a
        sub word[number_2], 30h ; b
    

        ; converting into a two digit integer
        mov ax, word[number_1];
        mov cx, 10;
        mov dx,0
        mul cx ; ax = ax * cx   ; actually dx:ax = ax * cx
        add ax, word[number_2]
        mov word[number], ax

        
        ; initializing counter and sum
        mov word[counter], 0
        mov word[sum],0
        jmp Loop

        Loop:
            ; check if value in counter is even
            mov ax, word[counter]
            mov bl, 2
            mov ah, 0
            div bl ; divides ax by bl (or somenumber) and puts the quotient in al and the remainder in ah. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".

            cmp ah,0 ; reminder is stored in ah
            je CounterEven
            ComeBackFromCounterEven :

            ; increment counter
            add word[counter],1
            
            ; comparing counter and the number 
            mov ax, word[counter]
            mov bx, word[number]
            cmp ax, bx
            jle Loop
            jg PrintSum

        PrintSum:

            ; printing sum

            ; seperating 4 digits sum
            ; seperating ones
            mov ax, word[sum]; sum is stored in ax
            mov bx , 10
            mov dx, 0
            div bx ; divides dxax by bx (or somenumber) and puts the quotient in ax and the remainder in dx. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".
            mov word[ones_answer], dx; reminder
            mov word[temp], ax;   quotient

            
            ; seperating tens
            mov ax, word[temp]; temp is stored in ax
            mov bx , 10
            mov dx, 0
            div bx ; divides dxax by bx (or somenumber) and puts the quotient in ax and the remainder in dx. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".
            mov word[tens_answer], dx; reminder
            mov word[temp], ax;   quotient
            

            ; seperating hundreds_answer
            mov ax, word[temp]; temp is stored in ax
            mov bx , 10
            mov dx, 0
            div bx ; divides dxax by bx (or somenumber) and puts the quotient in ax and the remainder in dx. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".
            mov word[hundreds_answer], dx; reminder
            mov word[thousands_answer], ax;   quotient
            
            ; converting integer digits to ascci
            add word[ones_answer], 30h
            add word[tens_answer], 30h
            add word[hundreds_answer], 30h
            add word[thousands_answer], 30h

            ; printing four digits of sum
            mov eax, 4
            mov ebx, 1
            mov ecx, thousands_answer
            mov edx, 1
            int 80h

            mov eax, 4
            mov ebx, 1
            mov ecx, hundreds_answer
            mov edx, 1
            int 80h

            mov eax, 4
            mov ebx, 1
            mov ecx, tens_answer
            mov edx, 1
            int 80h

            mov eax, 4
            mov ebx, 1
            mov ecx, ones_answer
            mov edx, 1
            int 80h

            ; Exiting
            jmp Exit

        CounterEven:
            ; add value of counter to sum
            mov ax, word[counter]
            add word[sum], ax
            jmp ComeBackFromCounterEven

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
