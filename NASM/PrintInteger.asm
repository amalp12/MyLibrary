section .data
    message1 db "Enter n",10,0
    new_line db 10

section .bss
    input :resb 1
    temp : resd 1



section .text
global _start:
  _start:
        mov eax , message1
        call printString
        mov dword[temp] , 987654321
        mov eax , dword[temp]
        call printInteger
        call exit
  
        ; call printIntegerBackwards
        ; call printNewLine
        ; input eax register  to integer
        printInteger:
            call reverseInteger
            call printIntegerBackwards
            ret
  
        ; output print integer at eax
        reverseInteger:
            mov ecx, 0
            
            _reverseIntegerLoop:

                ; eax has the integer to be printed backwards
                mov ebx, 10
                mov edx, 0  
                div ebx

                push edx; push the remainder
                add ecx, 1; increment the counter

                cmp eax, 0
                jne _reverseIntegerLoop

            ; store reversed integer back into eax
            ; ecx has the number of digits
            mov eax, 0
            mov dword[temp] , 1
            _storeToEaxReverseIntegerLoop:
                pop edx; pop the remainder
                
                ; save eax for later
                push eax
                ; mov the remiander to eax for multilpying
                mov eax, edx
                mov ebx , dword[temp]
                mul ebx ; multiply the remainder by temp counter
                
                ; save reminder for later
                push eax
                ; multiply temp counter by 10
                mov eax , dword[temp]
                mov ebx , 10
                mul ebx
                mov dword[temp] , eax

                ; add the remainder to eax
                pop ebx ; retriving reminder
                pop eax ; retriving eax
                add eax, ebx

                

                sub ecx, 1; decrement the counter
                cmp ecx, 0
                jne _storeToEaxReverseIntegerLoop
            
            ret

        ; input eax register  to integer
        ; output print integer at eax
        printIntegerBackwards:
            
            _printIntegerBackwardsLoop:

                ; eax has the integer to be printed backwards
                mov ebx, 10
                mov edx, 0  
                div ebx

                push eax; save quotient for later
                mov eax, edx
                call printOneDigitInteger
                



                ; restore the quotient
                pop eax
                cmp eax, 0
                jne _printIntegerBackwardsLoop
            ret
                


            

        printNewLine:
            ; printing new line
            mov eax, 4
            mov ebx, 1
            mov ecx, new_line
            mov edx, 1
            int 80h
            ret


        ; input eax register as a pointer tso the one digit integer
        ; output convert the integer to a character and print it out
        printOneDigitInteger:
  
            add eax , 30h
            mov dword[temp] , 0
            add dword[temp], eax
            mov eax,4
            mov ebx, 1
            mov ecx, temp  
            mov edx, 1
            int 80h
            ret
        

        ; input eax register as a pointer to the string
        ; output print string at eax
        printString:

            push eax ; save eax for later
            mov edx ,0 ; counter for length of string
            _printStringLoop:
                inc eax ; increment pointer to string
                inc edx ; increment length of string
                mov cl, [eax] ; get next character 
                cmp cl ,0 ; check if end of string
                jne _printStringLoop ; if not end of string, loop


            ; printing string
            mov eax, 4 ; print string
            mov ebx, 1 ; stdout
            pop ecx ; restore eax (argument)
            ; edx already has count

            int 80h ; call syscall

            ; return to caller
            ret

    
        exit:
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
            ret
