
section .data
msg1 db "Enter First String : ", 10 , 0
msg2 db "Enter Second String : ", 10 , 0

section .bss
    str1 : resb 50
    str2 : resb 50
    str3 : resb 50
    temp : resd 1
    temp2: resd 1
    i :resb 1
    j : resb 1

section .text
    global  _start:
        _start:
            mov eax, msg1
            call printString
            mov eax, str1
            call readString

            mov eax, msg2
            call printString
            mov eax, str2
            call readString

            mov eax, str1
            mov ebx, str2
            mov ecx, str3

            call concatStrings
            
            mov eax, str3
            call printString
            
            call exit
        
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
            pushad
            
            mov edx ,0 ; counter for length of string
            _stringLengthLoop:
                mov cl, [eax] ; get next character 
                cmp cl ,0 ; check if end of string
                inc eax ; increment pointer to string
                inc edx ; increment length of string
                jne _stringLengthLoop ; if not end of string, loop


            mov dword[temp], edx
            popad
            mov eax, dword[temp]


            ; return to caller
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





