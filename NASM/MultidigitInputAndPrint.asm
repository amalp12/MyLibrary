

section .data
    message1: db 'Enter A 32 bit Number :', 10
    message1_length: equ $ - message1

    message2: db 'The Entered Number is :', 10
    message2_length: equ $ - message2

    


section .bss
    result : resd 1
    input : resb 1
    input_length : resb 1
    counter : resb 1
    temp : resb 1
    input_buffer : resb 1
    temp_reverse : resd 1
    reverse_result : resd 1
    


section .text
    global _start:
        _start:
            ; printing message1
            mov eax , 4
            mov ebx , 1
            mov ecx , message1
            mov edx , message1_length
            int 80h

            

            ;zero out someplace to put result
            mov dword[result]  , 0
            mov byte[input] , 0
            jmp TakeInput


            TakeInput:
                
            
                TakeInputTop:



                    ;get a digit/character
                    mov eax, 3
                    mov ebx, 0
                    mov ecx, input
                    mov edx, 1
                    int 80h


                    
                    ;subtract '0' to convert character to number
                    
                    
                    mov eax, dword[input]

                    ;make sure it represents a decimal digit
                    cmp eax, '0'
                    ;(if not - go to done)
                    jl TakeInputDone
                    cmp eax, '9'
                    jg TakeInputDone


                    sub byte[input] , 30h
                    
                    ;multiply "result so far" by 10
                    mov eax, dword[result]
                    mov ebx, 10
                    mov edx, 0
                    mul ebx

                    mov dword[result] , eax


                    ;add in the new number
                    
                    mov eax, dword[input]
                    add dword[result] , eax 
                    
                    ;go to top
                    jmp TakeInputTop


                    TakeInputDone:
                    
                        
                        ;printing message2
                        mov eax , 4
                        mov ebx , 1
                        mov ecx , message2
                        mov edx , message2_length
                        int 80h
                        
                        ; moving 1 into counter
                        mov byte[counter] , 1
                        mov dword[reverse_result] , 0

                     
        
                        jmp PrintTop


                PrintTop:

                    StoreInStackStart:
                        mov eax, dword[result] ; quotient 
                        mov ebx, 10 
                        mov edx , 0 ; reminder
                        
                        div ebx

                        ; storing quotient in result
                        mov dword[result] , eax
                        
                 
                        add edx , 30h
                        ; storing remiander in stack
                        sub esp, 8
                        mov [esp], edx
                        

                        ;incrementing counter
                        add byte[counter] , 1

                        ; checking if the counter is greater than  number of digits
                        mov al , byte[counter]
                        cmp al , 10 

                        jg StoreInStackDone
                        jmp StoreInStackStart

                StoreInStackDone:
                    
                    jmp PrintStart

                PrintStart:
                    
                    ; printing digits from stack
                    mov eax , 4
                    mov ebx , 1
                    mov ecx, esp ; poping from stack
                    add esp , 8 ; decrementing stack (8 bytes)
                    mov edx , 1
                    int 80h

                    dec byte[counter] 
                    mov al , byte[counter]
                    cmp al , 1

                    jl Exit
                    jmp PrintStart


                    
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




                        


