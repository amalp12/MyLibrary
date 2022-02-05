
section .data
    message1: db 'Enter First Number to Add', 10
    message1_length: equ $ - message1

    message2: db 'Enter Second Number to Add', 10
    message2_length: equ $ - message2



section .bss
    input_buffer : resb 1
    number_1: resb 1
    number_2: resb 1
    first_digit_ans : resd 1
    second_digit_ans : resd 1



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

    ; Adding two numbers
    
    mov ax, word[number_1]
    add ax ,word[number_2]

    


    ; seperating two digits
    ; For DIV, the registers EDX and EAX form one single 64 bit value (often shown as EDX:EAX), which is then divided, in this case, by EBX.
    ; mov edx, 0 ; reminder will be stored here
    ; mov eax, [sum] ; quotient will be stored here
    ; mov ecx, 10 ; divisor
    ; div ecx

    ; sum is stored in ax
    mov bl , 10
    mov ah, 0
    div bl ; divides ax by bl (or somenumber) and puts the quotient in al and the remainder in ah. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".



    ; storing the first digit (one's place ) of the answer
    mov byte[first_digit_ans], ah ; reminder

    ; storing the second digit (ten's place ) of the answer
    mov byte[second_digit_ans], al ; quotient


    ; converting the result from integer to ascci
    add byte[first_digit_ans], 30h
    add byte[second_digit_ans], 30h
    


    ; printing the result



    ; printing the Second digit (ten's place ) of the answer
    mov eax, 4
    mov ebx, 1
    mov ecx, second_digit_ans
    mov edx, 1
    int 80h


    ; printing the First digit (one's place ) of the answer
    mov eax, 4
    mov ebx, 1
    mov ecx, first_digit_ans
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
