
section .data
msg1 db "Enter String : ", 10 , 0
msg2 db "Enter Second String : ", 10 , 0
msg3 db "The Strings are equal.", 10 , 0
msg4 db "The Strings are not equal.", 10 , 0



section .bss
    string : resb 50
    temp : resd 1
 

section .text
    global  _start:
        _start:
            mov eax, msg1
            call printString
            mov eax, string
            call readString
            mov eax, string
            call countSpaces
            call printInteger
            
            call exit
        ; input eax strings pointer output number of spaces eax
        countSpaces:
            
            mov ecx, 0
            countSpacesLoop:
                mov dl, byte[eax]
                cmp dl, 0
                je countSpacesLoopEnd

                cmp dl ,32
                je inc_ecx
                inc_ecx_return :
                inc eax
                jmp countSpacesLoop

            countSpacesLoopEnd:
                mov eax, ecx
                ret
                

            inc_ecx:
                inc ecx
                jmp inc_ecx_return
                

            popad
            ret
        compareStrings:
            pushad
            push dword[temp]

            compareStringsLength:
                push eax
                push ebx
                call stringLength
                mov dword[temp], eax
                pop ebx
                pop eax
                push eax
                push ebx

                mov eax, ebx
                call stringLength
                mov ebx, dword[temp]
                cmp eax, ebx
                jne stringsNotEqualLen
                
                pop ebx
                pop eax

                mov ecx, dword[temp]
            compareStringsLoop:
                cmp ecx, 0
                je stringsEqual
                mov dl, byte[eax]
                cmp byte[ebx], dl
                jne stringsNotEqual
                inc eax
                inc ebx
                dec ecx
                jmp compareStringsLoop



            stringsNotEqualLen:
                pop eax
                pop eax
                mov eax, msg4
                call printString
                pop dword[temp]
                popad
                ret

            stringsNotEqual:
                mov eax, msg4
                call printString
                pop dword[temp]
                popad
                ret
                
            stringsEqual:
                mov eax, msg3
                call printString
                pop dword[temp]
                popad
                ret
            
                
                


        ; input eax and ebx strings. ecx third string
        ; output third string 
        concatStrings:
            pushad
            push dword[temp]

            push eax
            push ebx
            
            ; dealing with first string 
            firstStrLoop:

                mov dl, byte[eax]
                cmp dl ,  0
                je firstStrLoopEnd

                mov byte[ecx], dl
            
                add eax, 1
                add ecx, 1
                jmp firstStrLoop

            firstStrLoopEnd:
             
                pop ebx
                pop eax
                

            ; dealing with second string 
            secondStrLoop:

                mov dl, byte[ebx]
                cmp dl ,  0
                je secondStrLoopEnd

                mov byte[ecx], dl
            
                add ebx, 1
                add ecx, 1
                jmp secondStrLoop

            secondStrLoopEnd:
                mov byte[ecx], 0 
                

            

            

            

            pop dword[temp]
            popad
            ret




            

        
        
        ; input string eax , string len ebx, output also eax
        reverseString:
            pushad
            
            
            ; mov dword[temp], ebx
            ; add dword[temp], 30h
            ; mov eax, 4
            ; mov ebx,1
            ; mov ecx, temp
            ; mov edx, 4
            ; int 80h

            mov dword[temp], ebx
            mov ebx, eax
            add ebx, dword[temp]
            
            

            reverseStringLoop:

                cmp eax, ebx
                jge reverseStringLoopEnd


                pushad
                mov dl, byte[ebx]
                mov byte[temp], dl

                mov dl, byte[eax]
                mov byte[ebx], dl

                mov dl, byte[temp]
                mov byte[eax], dl



                popad
                

                add eax, 1
                sub ebx, 1
                jmp reverseStringLoop


            reverseStringLoopEnd:
                popad
                ret

            
            ; ; i=0 j = n-1, while i<j swap elements , i++, j--
            ; reverseStringLoop:

                

            ; reverseStringLoopEnd:
            ;     popad
            ;     ret





        ; ; eax byte adress 1 and ebx byte address 2
        ; swapBytes:
        ;     pushad
        ;     movzx edx, byte[ebx]
        ;     push edx

        ;     mov cl , byte[ebx]
        ;     mov byte[eax], cl

        ;     pop ecx
        ;     mov byte[ebx], cl
        ;     popad
        ;     ret

        ; function to read string
        ; input eax should have ponter to empty string, output eax will have pointer to ouput string
        readString:
            
            push dword[temp]
            pushad
            mov ecx, 0
            readingLoop:
                push eax
                push ecx
                mov eax, 3
                mov ebx, 0
                mov ecx, temp
                mov edx, 1
                int 80h

                pop ecx
                pop eax


                cmp byte[temp], 10
                je readingLoopEnd

                mov bl, byte[temp]
                mov byte[eax+ecx], bl
                inc ecx




                jmp readingLoop


            readingLoopEnd:
                mov byte[eax+ecx], 0
                mov dword[temp], ecx
                

            
                popad
                mov ebx, dword[temp]
                pop dword[temp]
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

        ; input eax register as a pointer to the string
        ; output string length at eax
        stringLength:
            mov ecx,0 
            stringLengthLoop:
                mov dl, byte[eax+ecx]
                cmp dl, 0
                je stringLengthLoopEnd
                add  ecx, 1
                
                jmp stringLengthLoop


            stringLengthLoopEnd:
                mov eax, ecx      
                ret

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

        printNewLine:
                    ; printing new line
                    sub esp,1
                    mov byte[esp], 10
                    mov eax, 4
                    mov ebx, 1
                    mov ecx, esp
                    mov edx, 1
                    int 80h
                    add esp,1
            ret
        exit:
                
                call printNewLine



                    ; exit call
                    mov eax , 1
                    mov ebx , 0
                    int 80h
                    ret





