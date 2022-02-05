
section .data
    message1: db 'Enter First Digit of First Number to Add', 10
    message1_length: equ $ - message1

    message2: db 'Enter Second Digit of First Number to Add', 10
    message2_length: equ $ - message2

    message3: db 'Enter First Digit of Second Number to Add', 10
    message3_length: equ $ - message3

    message4: db 'Enter Second Digit of Second Number to Add', 10
    message4_length: equ $ - message4



section .bss
    input_buffer : resb 1
    number_1_1: resb 1
    number_1_2: resb 1
    number_2_1: resb 1
    number_2_2: resb 1

    carry: resb 1
    ones_answer: resb 1
    tens_answer: resb 1
    hundreds_answer: resb 1




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



    ; printing message2
    mov eax , 4
    mov ebx , 1
    mov ecx , message2
    mov edx , message2_length
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



    ; printing message2
    mov eax , 4
    mov ebx , 1
    mov ecx , message2
    mov edx , message2_length
    int 80h


    ; Taking second number second digit input
    mov eax, 3
    mov ebx, 0
    mov ecx, number_2_2;
    mov edx, 1;
    int 80h

    


    ; converting both numbers from ascci to integer
    sub byte[number_1_1], 30h ; a
    sub byte[number_1_2], 30h ; b
    sub byte[number_2_1], 30h ; c
    sub byte[number_2_2], 30h ; d
    ; ab + cd = one's -> (b+d) , Tens -> (a+c) if no carryl; else one's -> (b+d) , Tens -> (a+c+ carry )   
  
    ; b+d
    mov ax, word[number_1_2]
    add ax, word[number_2_2]

    


    ; seperating two digits of b+d
   

    ; sum is stored in ax
    mov bl , 10
    mov ah, 0
    div bl ; divides ax by bl (or somenumber) and puts the quotient in al and the remainder in ah. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".



    ; storing the first digit (one's place ) of the answer
    mov byte[ones_answer], ah ; reminder

    ; storing the carry (ten's place of b+d) 
    mov byte[carry], al ; quotient

    ; a+c + carry
    mov ax, word[number_1_1]
    add ax, word[number_2_1]
    add ax, word[carry]

    ; seperating two digits of b+d+ carry
    ; sum is stored in ax
    mov bl , 10
    mov ah, 0
    div bl ; divides ax by bl (or somenumber) and puts the quotient in al and the remainder in ah. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".



    ; storing the first digit (one's place ) of the answer
    mov byte[tens_answer], ah ; reminder

    ; storing the carry (ten's place of b+d) 
    mov byte[hundreds_answer], al ; quotient


    ; converting the result from integer to ascci
    add byte[ones_answer], 30h
    add byte[tens_answer], 30h
    add byte[hundreds_answer], 30h


    


    ; printing the result

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
