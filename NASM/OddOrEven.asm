
section .data
    message: db 'Enter Number :', 10
    message_length: equ $ - message

    messageEven: db 'The Entered Number is Even', 10
    messageEven_length: equ $ - messageEven

    messageOdd: db 'The Entered Number is Odd', 10
    messageOdd_length: equ $ - messageOdd
  


section .bss
    input_buffer : resb 1
    number: resb 1




section .text
global _start:
    _start:

        ; printing message
        mov eax , 4
        mov ebx , 1
        mov ecx , message
        mov edx , message_length
        int 80h

        ; Taking  number input
        mov eax, 3
        mov ebx, 0
        mov ecx, number;
        mov edx, 1;
        int 80h

        ; coverting number froma ascci to integer
        sub byte[number], 30h

        ; checking if number is divisible by two
        mov ax , word[number]
        mov bl , 2
        mov ah , 0
        div bl
        cmp ah , 0
        je Even
        jnp Odd



    Even:
        ; printing message
        mov eax , 4
        mov ebx , 1
        mov ecx , messageEven
        mov edx , messageEven_length
        int 80h

        jmp Exit

    Odd:
        ; printing message
        mov eax , 4
        mov ebx , 1
        mov ecx , messageOdd
        mov edx , messageOdd_length
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
