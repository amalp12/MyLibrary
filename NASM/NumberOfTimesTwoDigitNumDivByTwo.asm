
section .data
    message1: db 'Enter First Digit of Number :', 10
    message1_length: equ $ - message1

    message2: db 'Enter Second Digit of Number :', 10
    message2_length: equ $ - message2

    messageEven: db 'The number of times the given number is divisible by 2 is :', 10
    messageEven_length: equ $ - messageEven

    messageOdd: db 'The Entered Number is Odd, Please Enter an Even Number.', 10
    messageOdd_length: equ $ - messageOdd
  


section .bss
    input_buffer : resb 1
    number_1: resb 1
    number_2: resb 1
    counter: resb 1
    number: resw 1




section .text
global _start:
    _start:

        ; printing message
        mov eax , 4
        mov ebx , 1
        mov ecx , message1
        mov edx , message1_length
        int 80h

        ; Taking  number input
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

        ; coverting number from ascci to integer
        sub byte[number_1], 30h
        sub byte[number_2], 30h

        ; checking if number is divisible by two
        mov ax , word[number_2]
        mov bl , 2
        mov ah , 0
        div bl
        cmp ah , 0
        je Even
        jnp Odd



    Even:

        ; converting two digits into single number
        mov ax , word[number_1]
        mov cx , 10
        mov dx, 0
        mul cx ; ax = ax * cx   ; actually dx:ax = ax * cx
        
        add ax , word[number_2]
        mov word[number] , ax
        ; now number contains the two digit number

        ; initializing counter
        mov byte[counter] , 0

        ; moving number to ax for looped division
        mov ax, word[number]; number is stored in ax
        jmp Loop

        jmp Exit

    Odd:
        ; printing message
        mov eax , 4
        mov ebx , 1
        mov ecx , messageOdd
        mov edx , messageOdd_length
        int 80h

        jmp Exit


    Loop:
        ; dividing number by 2
        
        ;ax   quotient has the current number
        mov bx , 2
        mov dx, 0
        div bx ; divides dx:ax by bx (or somenumber) and puts the quotient in ax and the remainder in dx. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".
        ; dx reminder
        ; checking if reminder is zero and then incrementing counter if it is
        cmp dx , 0
        jne PrintFinal
        inc byte[counter]
        jmp Loop
  
    PrintFinal:
        ; printing message
        mov eax , 4
        mov ebx , 1
        mov ecx , messageEven
        mov edx , messageEven_length
        int 80h

        ; printing counter
        add byte[counter] , 30h
        mov eax , 4
        mov ebx , 1
        mov ecx , counter
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
