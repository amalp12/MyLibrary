
section .data
    msg1 db "The Given string is a palindrome", 10, 0
    msg2 db "The Given string is not a palindrome", 10, 0


section .bss
    string : resb 50
    temp : resb 1

section .text
    global  _start:
        _start:
            mov eax, string
            call readString
            mov eax, string

            call isPalindrome
            call exit
           
          ; input string eax , string len ebx, output also eax
        isPalindrome:
            pushad
            push dword[temp]
 

            mov dword[temp], ebx
            mov ebx, eax
            add ebx, dword[temp]
            dec ebx
            
            
            

            isPalindromeLoop:

                
                cmp eax, ebx
                jge isPalindromeDone

                mov cl, byte[eax]
                mov ch, byte[ebx]
                cmp byte[eax], ch

                


                jne notPalindrome

              

                add eax, 1
                sub ebx, 1
                
                jmp isPalindromeLoop


            isPalindromeDone:
                mov eax, msg1
                call printString
                pop dword[temp]
                popad
                ret

            notPalindrome:
                mov eax, msg2
                call printString
                pop dword[temp]
                popad
                ret

            
            ; ; i=0 j = n-1, while i<j swap elements , i++, j--
            ; isPalindromeLoop:

                

            ; isPalindromeLoopEnd:
            ;     popad
            ;     ret





        ; ; eax byte adress 1 and ebx byte address 2
        ; swapBytes:
            
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





