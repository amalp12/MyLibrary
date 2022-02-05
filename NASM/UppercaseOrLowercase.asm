
section .data
    message1: db 'Enter an Alphabet:', 10
    message1_length: equ $ - message1

    messageUpper: db 'This Alphabet is Uppercase', 10
    messageUpper_length: equ $ - messageUpper

    messageLower: db 'This Alphabet is Lowercase', 10
    messageLower_length: equ $ - messageLower

    messageNotAlphabet: db 'The Entered Character is Not an Alphabet', 10
    messageNotAlphabet_length: equ $ - messageNotAlphabet



section .bss
    input_buffer: resb 10
    input_alphabet: resb 1
    greater_than_A: resb 1
    less_than_Z: resb 1
    alphabet_is_upper: resb 1

    greater_than_a : resb 1
    less_than_z : resb 1
    alphabet_is_lower: resb 1






section .text
global _start:
    _start:

    ; printing message1
    mov eax , 4
    mov ebx , 1
    mov ecx , message1
    mov edx , message1_length
    int 80h

    ; Taking input Alphabet
    mov eax, 3
    mov ebx, 0
    mov ecx, input_alphabet;
    mov edx, 1;
    int 80h

    ; Taking junk input
    mov eax, 3
    mov ebx, 0
    mov ecx, input_buffer;
    mov edx, 1;
    int 80h

    ; initializing all boolean variables to 0
    mov byte[greater_than_A], 0
    mov byte[less_than_Z], 0
    mov byte[alphabet_is_upper], 0
    mov byte[greater_than_a], 0

    ; Checking if the input is Uppercase
    mov al , byte[input_alphabet]
    cmp al , 'A'
    jge set_greater_than_A
    come_back_A:

    mov al , byte[input_alphabet]
    cmp al , 'Z'
    jle set_less_than_Z
    come_back_Z:

    mov al, byte[greater_than_A]
    and  al ,  byte[less_than_Z]
    mov byte[alphabet_is_upper], al

    ; Checking if the input is Lowercase
    mov al , byte[input_alphabet]
    cmp al , 'a'
    jge set_greater_than_a
    come_back_a:


    mov al, byte[input_alphabet]
    cmp al, 'z'
    jle set_less_than_z
    come_back_z:

    mov al, byte[greater_than_a]
    and al, byte[less_than_z]
    mov byte[alphabet_is_lower], al


    ; if is Uppercase
    mov al , byte[alphabet_is_upper]
    cmp al , 1
    je Uppercase

    ; if is Lowercase
    mov al , byte[alphabet_is_lower]
    cmp al , 1
    je Lowercase

    ; if is not an Alphabet
    jmp NotAlpha

    Uppercase:
        mov eax , 4
        mov ebx , 1
        mov ecx , messageUpper
        mov edx , messageUpper_length
        int 80h
        jmp Exit
    
    Lowercase:
        mov eax , 4
        mov ebx , 1
        mov ecx , messageLower
        mov edx , messageLower_length
        int 80h
        jmp Exit

    NotAlpha:
        mov eax , 4
        mov ebx , 1
        mov ecx , messageNotAlphabet
        mov edx , messageNotAlphabet_length
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

    set_greater_than_A:
        mov byte[greater_than_A] , 1
        jmp come_back_A

    set_greater_than_a:
        mov byte[greater_than_a] , 1
        jmp come_back_a

    set_less_than_Z:
        mov byte[less_than_Z] , 1
        jmp come_back_Z

    set_less_than_z:
        mov byte[less_than_z] , 1
        jmp come_back_z

 
   