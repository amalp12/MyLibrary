section .data
    message : db "Please Enter a Number Between 0 and 9: ",10
    message_length: equ $-message

section .bss
    input : resb 1
    input_length : resb 1
    counter: resb 1

section .text
global _start:
    _start:
        
        mov eax, 4;
        mov ebx, 1;
        mov ecx, message;
        mov edx, message_length;
        int 80h;

        mov eax, 3;
        mov ebx, 0;
        mov ecx, input;
        mov edx, input_length;
        int 80h;

        sub byte[input] , 30h ; converting sting number to integer
        mov byte[counter],0 ; initializing counter to 0


        Loop:

            add byte[counter], 30h; changing counter value from integer to ascci for printing


            mov eax, 4;
            mov ebx, 1;
            mov ecx, counter;
            mov edx, 1;
            int 80h;


            sub byte[counter] , 30h ; converting string number to integer
            add byte[counter], 1 ; incrementing counter


            mov al , byte[counter];
            cmp al, byte[input] ; checking if counter is input

            ;jne Loop ; if not equal to input then go to loop
            jna Loop ; if not equal to input then go to loop



        mov eax, 1;
        mov ebx, 0;
        int 80h; 

