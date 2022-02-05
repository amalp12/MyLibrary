
section .data
    message1: db 'Enter First Digit of the Number to Square', 10
    message1_length: equ $ - message1

    message2: db 'Enter Second Digit of the Number to Square', 10
    message2_length: equ $ - message2




section .bss
    input_buffer : resb 1
    number_1_1: resb 1
    number_1_2: resb 1

    carry: resb 1
    ones_answer: resb 1
    tens_answer: resb 1
    hundreds_answer: resb 1
    thousands_answer: resb 1




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




        ; converting both numbers from ascci to integer
        sub byte[number_1_1], 30h ; a
        sub byte[number_1_2], 30h ; b
    

        ;ones = b*b
        mov ax , word[number_1_2]
        mov cx , word[number_1_2]
        mul cx ; ax = ax * cx   ; actually dx:ax = ax * cx
        


        ; seperating two digits of b*b
    

        ; product is stored in ax
        mov bl , 10
        mov ah, 0
        div bl ; divides ax by bl (or somenumber) and puts the quotient in al and the remainder in ah. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".



        ; storing the first digit (one's place ) of the answer
        mov byte[ones_answer], ah ; reminder

        ; storing the carry (ten's place of b+d) 
        mov byte[carry], al ; quotient

        ;tens_answer = 2*ab
        mov ax, word[number_1_1]
        mov cx, word[number_1_2]
        mul cx ; ax = ax * cx   ; actually dx:ax = ax * cx
        add ax , ax ; 2* (ab)
        add ax, word[carry]

        ; seperating two digits of 2*ab

        ; sum is stored in ax
        mov bl , 10
        mov ah, 0
        div bl ; divides ax by bl (or somenumber) and puts the quotient in al and the remainder in ah. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".



        ; storing the first digit (one's place ) of the answer
        mov byte[tens_answer], ah ; reminder

        ; storing the carry (ten's place of b+d) 
        mov byte[carry], al ; quotient

        ; hundreds_answer = a*a + carry
        mov ax, word[number_1_1]
        mov cx, word[number_1_1]
        mul cx ; ax = ax * cx   ; actually dx:ax = ax * cx
        add ax, word[carry]


        ; seperating two digits of a*a+carry

        ; sum is stored in ax
        mov bl , 10
        mov ah, 0
        div bl ; divides ax by bl (or somenumber) and puts the quotient in al and the remainder in ah. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".



        ; storing the first digit (one's place ) of the answer
        mov byte[hundreds_answer], ah ; reminder

        ; storing the carry (ten's place of b+d) 
        mov byte[thousands_answer], al ; quotient

        




        ; converting the result from integer to ascci
        add byte[ones_answer], 30h
        add byte[tens_answer], 30h
        add byte[hundreds_answer], 30h
        add byte[thousands_answer], 30h


        


        ; printing the result

        ; printing the third digit (thousand's place ) of the answer
        mov eax, 4
        mov ebx, 1
        mov ecx, thousands_answer
        mov edx, 1
        int 80h

        ; printing the third digit (hundred's place ) of the answer
        mov eax, 4
        mov ebx, 1
        mov ecx, hundreds_answer
        mov edx, 1
        int 80h


        ; printing the Second digit (ten's place ) of the answer
        mov eax, 4
        mov ebx, 1
        mov ecx, tens_answer
        mov edx, 1
        int 80h


        ; printing the First digit (one's place ) of the answer
        mov eax, 4
        mov ebx, 1
        mov ecx, ones_answer
        mov edx, 1
        int 80h


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
