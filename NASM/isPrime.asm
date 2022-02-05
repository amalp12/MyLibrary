; C/C++ Implemenation for isPrime
; int isPrime(int num )
; {
;     // 2 is the only even prime number
;     if(num==2) return 1;
;     // all other even numbers are not prime
;     if(num%2==0) return 0;
;     // now we know that num is odd and greater than 2 so we need to check only till sqrt(num)
;     for(int i = 3; i<=sqrt(num); i+=2) if(num%i==0) return 0;
;     return 1;
; }


section .data
    message1: db 'Enter First Digit of First Number to Check if Prime :', 10
    message1_length: equ $ - message1

    message2: db 'Enter Second Digit of First Number to Check if Prime  :', 10
    message2_length: equ $ - message2

    messagePrime: db 'The Number is Prime', 10
    messagePrime_length: equ $ - messagePrime

    messageNotPrime: db 'The Number is Not Prime', 10
    messageNotPrime_length: equ $ - messageNotPrime

 


section .bss
    input_buffer : resb 1
    number_1_1: resw 1
    number_1_2: resw 1
    counter : resw 1


    num : resw 1





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

   


    ; converting both numbers from ascci to integer
    sub word[number_1_1], 30h ; a
    sub word[number_1_2], 30h ; b

    

    ; converting two digits into single number
    mov ax , word[number_1_1]
    mov cx , 10
    mov dx, 0
    mul cx ; ax = ax * cx   ; actually dx:ax = ax * cx
    
    add ax , word[number_1_2]
    mov word[num] , ax
    ; now num contains the first two digit number

    ; 2 is the only even prime number
    ; if(num==2) return prime;
    cmp word[num], 2
    je isPrime_END_PRIME

    ; initializing counter
    mov word[counter],3 ; initializing counter to 3

    ; checking if the given number is prime or not 
    jmp isPrime

    isPrime:
        
        ; checking if the counter greater or equal to the given number
        mov ax, word[counter]
        cmp ax, word[num]
        jge isPrime_END_PRIME
        
        ; all other even numbers are not prime, so we only need to check odd numbers

        ; dividing number by value in counter
        
        mov ax, word[num] ;   quotient has the current number
        mov bx , word[counter] ; divisor has the current counter value
        mov dx, 0
        div bx ; divides dx:ax by bx (or somenumber) and puts the quotient in ax and the remainder in dx. If the quotient won't fit in al (if ah >= bl), it raises an exception. This exception is sometimes reported as "divide by zero error" or "floating point error".
        ; dx reminder


        ; checking if the reminder is zero then it is not a prime
        cmp dx , 0
        je isPrime_END_NOTPRIME

        ; incrementing counter
        add word[counter], 2

        ; else repeat loop
        jmp isPrime
    
    isPrime_END_PRIME:
        ; print message
        mov eax , 4
        mov ebx , 1
        mov ecx , messagePrime
        mov edx , messagePrime_length
        int 80h


        jmp Exit
    
    isPrime_END_NOTPRIME:
        ; print message
        mov eax , 4
        mov ebx , 1
        mov ecx , messageNotPrime
        mov edx , messageNotPrime_length
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
