

section .data
    message1 db 'Enter n :', 10,0
    message2 db 'Enter elements of array :', 10,0
    message3 db 'The Sum of All Elements in Array is  :', 10,0
    message4 db 'The Average of All Elements in Array is :', 10,0
    NEW_LINE db 10    

    array times 50 db 0

section .bss
    temp : resb 1
    ;array : resb 50

    


section .text
    global _start:
        _start:
            mov eax, message1
            call printString

            ; getting n
            call TakeIntegerInput ; n stored in eax
            push eax ; saving n for later
            mov eax, message2
            call printString
            pop eax ; retrieving n from stack
            push eax; saving n for later , here we just peeked the value
            
            ; taking n inputs from the user
            mov ebx, eax
            mov eax, array
            call TakeNIntegerInputs ; now array is filled with n inputs
            

            mov eax, array
            pop ebx ; retrieving n from stack
            push ebx ; saving n for later

            ;printing the array
            call sumOfElementsInArray
            
            pushad
            mov eax, message3
            call printString
            popad
            call printInteger
            pushad
            call printNewLine
            mov eax, message4
            call printString
            popad

            pop ebx
            mov eax, array
            call averageOfElementsInArray

            call printInteger

            call exit









            ; input eax array adress, ebx number of elements   
            ; output average of elements in eax and reminder in ebx
            averageOfElementsInArray:
                push ebx
                call sumOfElementsInArray
                pop ebx
                mov edx,0
                div ebx
                mov ebx, edx
                ret


            ; input eax array adress, ebx number of elements
            ; output sum of elements in eax
            sumOfElementsInArray:
                mov ecx, ebx ; setting counter
                mov ebx, eax ; moving array to ebx for convinience 
                mov edx, 0; setting edx (sum) to 0
         
                _sumOfElementsInArrayLoop:

                    ; saving ecx and ebx for later
                    ;add ebx,2

                    ; modify this part to change the size of each array element
                    movzx eax, byte[ebx] ; getting the value at the current index
                    

                    add edx, eax ; adding the value to the sum
                    
                    

                    add ebx, 1 ; incrementing the index


                    dec ecx ; decrementing the counter
                    cmp ecx, 0 ; checking if the counter is zero
                    jnz _sumOfElementsInArrayLoop
                
                mov eax, edx ; returning the sum
                ret


            ; input eax array adress, ebx number of elements
            ; output eax number of Odd numbers
            numberOfOddsInArray:
                push ebx
                call numberOfEvensInArray
                pop ebx
                sub ebx, eax
                mov eax, ebx
                ret


            ; input eax array adress, ebx number of elements
            ; output eax number of even numbers
            numberOfEvensInArray:
                mov ecx, ebx ; setting counter
                mov ebx, eax ; moving array to ebx for convinience 
                mov dword[temp], 0
         
                _numberOfOddsAndEvensInArrayLoop:

                   

                    ; modify this part to change the size of each array element
                    movzx eax, byte[ebx] ; getting the value at the current index
                    
                    push ebx
                    push ecx
                    call isEven
                    add dword[temp], eax
                    
                    ; getting back ecx and ebx
                    pop ecx                
                    pop ebx
                   
                    add ebx, 1 ; incrementing the index


                    dec ecx ; decrementing the counter
                    cmp ecx, 0 ; checking if the counter is zero
                    jnz _numberOfOddsAndEvensInArrayLoop
                
                mov eax, dword[temp]
                ret
 

            ; input eax has the integer
            ; output eax 1 if even else 0
            isEven:
                mov ebx, 2
                mov edx, 0
                div ebx
            
                cmp edx, 0
                je _integerisEven
                mov eax, 0
                ret
                _integerisEven:
                    mov eax, 1
                    ret
            ; input eax with array address, ebx with array size and ecx the element to be searched
            ; output eax elmement postion and ebx with boolean if found or not
            linearSearchIntegerArray:
                mov edx, ecx ; element to be searched
                mov ecx, ebx ; setting counter
                mov ebx, eax ; moving array to ebx for convinience 
                mov dword[temp], 0 ; setting temp to 0
                _linearSearchIntegerArrayLoop:

                    ; saving ecx and ebx for later
                    ;add ebx,2

                    ; modify this part to change the size of each array element
                    movzx eax, byte[ebx] ; getting the value at the current index
                    

                    
                    cmp eax, edx
                    je _linearSearchIntegerArrayFound
                    add ebx, 1 ; incrementing the arrau adress
                    add dword[temp], 1 ; incrementing the index


                    dec ecx ; decrementing the counter
                    cmp ecx, 0 ; checking if the counter is zero
                    jnz _linearSearchIntegerArrayLoop
                
                mov eax,0
                mov ebx,0
                ret
                _linearSearchIntegerArrayFound:
                    mov eax, dword[temp]
                    mov ebx , 1
                    ret


            ; input give an array in eax and the length of the array in ebx
            ; output is printing all the values of the array, there is no return value
            PrintIntegerArray:
                mov ecx, ebx ; setting counter
                mov ebx, eax ; moving array to ebx for convinience 

         
                _PrintIntegerArrayLoop:

                    ; saving ecx and ebx for later
                    ;add ebx,2

                    ; modify this part to change the size of each array element
                    movzx eax, byte[ebx] ; getting the value at the current index
                    

                    
                    push ecx
                    push ebx
                    call printInteger
                    
                    ; getting back ecx and ebx
                    pop ebx
                    pop ecx
                    add ebx, 1 ; incrementing the index


                    dec ecx ; decrementing the counter
                    cmp ecx, 0 ; checking if the counter is zero
                    jnz _PrintIntegerArrayLoop
                
                ret



            
            
            ; input give an array in eax and the length of the array in ebx
            ; output the array will be fillled with n inputs and eax will point to the end of the array
            TakeNIntegerInputs:

                mov ecx, ebx ; setting counter
                mov ebx, eax ; moving array to ebx for convinience 
                


                _TakeNIntegerInputsLoop:
                    
                    ; saving ecx and ebx for later
                    push ecx
                    push ebx
                    call TakeIntegerInput ; input intefer stored in eax
                    ; getting back ecx and ebx
                    pop ebx
                    pop ecx

                    ; modify this part to change the size of each array element
                    mov byte[ebx], al
                    add ebx, 1 ; incrementing the pointer to array to next memory location

        

                    cmp ecx, 0 ; checking if counter is zero
                    sub ecx,1 ; decrementing the counter
                    
                    
                    jne _TakeNIntegerInputsLoop ; if not zero then loop again

                mov eax, ebx ; moving array pointer to eax
                ret






            ; inputteed integer will to stored in eax
            TakeIntegerInput:
                mov eax,0; set result to zeroi intially
                ; get input integer from user and it will be stored in eax
                _TakeIntegerInputLoop:

                    mov dword[temp], 0 ; setting temp to zero
                    ; save result for later
                    push eax
                    ;get a digit/character
                    mov eax, 3
                    mov ebx, 0
                    mov ecx, temp
                    mov edx, 1
                    int 80h

                    pop eax ; get saved result from stack

                    

                    ;make sure it represents a decimal digit
                    mov ebx, dword[temp]
                    cmp ebx, '0'
                    ;(if not - go to done)
                    jl _TakeIntegerInputLoopDone
                    cmp ebx, '9'
                    jg _TakeIntegerInputLoopDone


                    ;subtract '0' to convert character to number
                    sub dword[temp] , 30h
                    
                    ;multiply "result so far" by 10
                    mov ebx, 10
                    mov edx, 0
                    mul ebx


                    ;add in the new number
                    add eax, dword[temp]
                    
                    ;go to top
                    jmp _TakeIntegerInputLoop


                    _TakeIntegerInputLoopDone:
                    
                        ret
                        


       ; input ascci in eax
       ; output 1 is its in integer and 0 if its not in eax
       isInteger:
         cmp ebx, '0'
        ;(if not - go to done)
        jl _isIntegerLessThanZero
        cmp ebx, '9'
        jg _isIntegerGreaterThanZero
            mov eax, 1
            ret
        _isIntegerLessThanZero:
            mov eax, 0
            ret
        _isIntegerGreaterThanZero:
            mov eax, 0
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
                


            

        printNewLine:
            ; printing new line
            mov eax, 4
            mov ebx, 1
            mov ecx, NEW_LINE
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


        takeBufferInput:
            mov eax, 3
            mov ebx, 0
            mov ecx, temp
            mov edx, 1
            ret
    
        exit:
           
           call printNewLine



            ; exit call
            mov eax , 1
            mov ebx , 0
            int 80h
            ret
