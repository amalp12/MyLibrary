; C/C++ Implemenation for Euclid's algorithm GCD Non Recursive
; int gcd(int a, int b)
; {
;     int c;
;     while (b != 0)
;     {
;         c = a % b;
;         a = b;
;         b = c;
;     }
;     return a;
; }


section .data
    message1: db 'Enter First Digit of First Number to find GCD of  :', 10
    message1_length: equ $ - message1

    message2: db 'Enter Second Digit of First Number to find GCD of  :', 10
    message2_length: equ $ - message2

    message3: db 'Enter First Digit of Second Number to find GCD of  :', 10
    message3_length: equ $ - message3

    message4: db 'Enter Second Digit of Second Number to find GCD of', 10
    message4_length: equ $ - message4

    message5: db 'The GCD of the Entered Numbers is :', 10
    message5_length: equ $ - message5



section .bss
    input_buffer : resb 1
    number_1_1: resw 1
    number_1_2: resw 1
    number_2_1: resw 1
    number_2_2: resw 1

    num_1 : resw 1
    num_2 : resw 1





section .text
global _start:
    _start:

    ; printing message1
    mov eax , 4
    mov ebx , 1
    mov ecx , message1
    mov edx , message1_length
    int 80h

    ; Taking first number first digit input
    mov eax, 3
    mov ebx, 0
    mov ecx, number_1_1;
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


    ; Taking first number second digit input
    mov eax, 3
    mov ebx, 0
    mov ecx, number_1_2;
    mov edx, 1;
    int 80h

    ; Taking junk input
    mov eax, 3
    mov ebx, 0
    mov ecx, input_buffer;
    mov edx, 1;
    int 80h



    ; printing message3
    mov eax , 4
    mov ebx , 1
    mov ecx , message3
    mov edx , message3_length
    int 80h


    ; Taking second number first digit input
    mov eax, 3
    mov ebx, 0
    mov ecx, number_2_1;
    mov edx, 1;
    int 80h

    ; Taking junk input
    mov eax, 3
    mov ebx, 0
    mov ecx, input_buffer;
    mov edx, 1;
    int 80h



    ; printing message4
    mov eax , 4
    mov ebx , 1
    mov ecx , message4
    mov edx , message4_length
    int 80h


    ; Taking second number second digit input
    mov eax, 3
    mov ebx, 0
    mov ecx, number_2_2;
    mov edx, 1;
    int 80h

    


    ; converting both numbers from ascci to integer
    sub word[number_1_1], 30h ; a
    sub word[number_1_2], 30h ; b
    sub word[number_2_1], 30h ; c
    sub word[number_2_2], 30h ; d
    

    ; converting two digits into single number
    mov ax , word[number_1_1]
    mov cx , 10
    mov dx, 0
    mul cx ; ax = ax * cx   ; actually dx:ax = ax * cx
    
    add ax , word[number_1_2]
    mov word[num_1] , ax
    ; now num_1 contains the first two digit number

    mov ax , word[number_2_1]
    mov cx , 10
    mov dx, 0
    mul cx ; ax = ax * cx   ; actually dx:ax = ax * cx
    
    add ax , word[number_2_2]
    mov word[num_2] , ax
    ; now num_2 contains the second two digit number

    ; calculating gcd of both numbers
    jmp GCD

    GCD:
        ; c = a % b
        mov ax, word[num_1]; a is stored in ax
        mov bx , word[num_2]; b is stored in bx
        mov dx, 0
        div bx ; divides dx : ax by bx (or somenumber) and puts the quotient in ax and the remainder in dx. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".
        ; dx - reminder ;c
        ; ax -  quotient
        mov ax, word[num_2]
        mov word[num_1] , ax ; a = b
        mov word[num_2] , dx ; b = c

        ; if b = 0 then exit
        mov ax, word[num_2]
        cmp ax, 0
        je GCD_END

        ; else repeat loop
        jmp GCD
    
    GCD_END:
        ; print message
        mov eax , 4
        mov ebx , 1
        mov ecx , message5
        mov edx , message5_length
        int 80h

        ; seperating two digits of gcd
        mov ax, word[num_1]; temp is stored in ax
        mov bx , 10
        mov dx, 0
        div bx ; divides dxax by bx (or somenumber) and puts the quotient in ax and the remainder in dx. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".
        mov word[num_2], dx; reminder
        mov word[num_1], ax;   quotient

        ; converting gcd from integer to ascci
        add word[num_2], 30h ; 
        add word[num_1], 30h ; 



        ; print gcd
        mov eax , 4
        mov ebx , 1
        mov ecx , num_1 ;
        mov edx , 1
        int 80h


        mov eax , 4
        mov ebx , 1
        mov ecx , num_2 ;
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
