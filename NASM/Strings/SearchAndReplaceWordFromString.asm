section .data
    msg1 db "Enter String ",10,0
    msg2 db "Enter Word to search ",10,0
    msg3 db "Enter Word to replace the searched word with ",10,0


  



section .bss

    string1: resb 5000
    string2: resb 5000
    string3: resb 5000

    temp : resd 1
    string_end : resb 1
    string_len : resb 1
    bool : resb 1

section .text

    global _start:
     _start:

        mov esi, msg1
        call print_string
        mov edi, string1
        call read_2D_sentance
        mov esi, string1
        ;call print_2d_string

        ;call print_new_line

        mov esi, msg2
        call print_string
        mov edi, string2
        call read_2D_sentance
        mov esi, string2
        ;call print_2d_string

        mov esi, msg3
        call print_string
        mov edi, string3
        call read_2D_sentance
      



        mov esi, string2
        mov edi, string1
        mov eax, string3
        call find_and_replace_word
        mov esi, string1
        call print_2d_string


        

        call exit
find_and_replace_word:
    ; esi contains word, edi contains string
    pushad
    push dword[temp]
    find_loop:

        ; esi  should not change, edi inc by 50
        push esi
        push edi

        call match_word
        cmp byte[bool], 1


        pop edi
        pop esi
        je found_replace
        add edi, 50

        cmp byte[edi], -1
        je find_and_replace_word_end


    jmp find_loop
    found_replace:
        mov esi, eax
        call string_length
        mov ecx, dword[string_len]
        inc ecx
        rep movsb
        

    






    find_and_replace_word_end:
        pop dword[temp] 
        popad
        ret





match_word :

    ; take a word and match it with another word
    ; first find string length
    ; esi has first word and edi has second
    pushad
    push dword[temp]
    push esi
    push edi
    call string_length
    mov eax, dword[string_len]
    mov esi, edi
    call string_length
    pop edi
    pop esi
    cmp dword[string_len], eax
    jne match_word_end

    ; length same
    mov ecx, dword[string_len]
    match_word_loop:
        cmpsb
        jne match_word_end
        loop match_word_loop

        pop dword[temp]
        popad
        mov byte[bool], 1
        ret
    



    match_word_end:


        pop dword[temp]
        popad
        mov byte[bool], 0
        ret




    
read_2D_sentance:

    push dword[temp]
    pushad
    mov byte[string_end], 0
    read_2D_sentance_loop:
        cmp byte[string_end], 1
        je read_2D_sentance_loop_end
        call read_word
        add edi, 50
        
    jmp read_2D_sentance_loop

    read_2D_sentance_loop_end:
        mov byte[edi], -1
        popad
        pop dword[temp]
        ret


print_2d_string:
    pushad
    push dword[temp]
    print_2d_string_loop:
        
        call print_string
        call print_space
        add esi, 50
        cmp byte[esi], -1
        je print_2d_string_loop_end
        



    jmp print_2d_string_loop

    print_2d_string_loop_end:
        
        pop dword[temp]
        popad
        ret        



string_length:

    pushad
    push dword[temp]
    mov ecx, 0

        string_length_loop:
            lodsb
            cmp al ,0
            je string_length_loop_end

            inc ecx 

        jmp string_length_loop
        
    string_length_loop_end:
        mov dword[string_len], ecx
        pop dword[temp]
        popad
        ret

print_new_line:
    pushad
    push dword[temp]
        mov byte[temp], 10
        mov eax, 4
        mov ebx, 1
        mov ecx, temp
        mov edx, 1
        int 80h

    pop dword[temp]
    popad
    ret
print_space:
    pushad
    push dword[temp]
        mov byte[temp], 32
        mov eax, 4
        mov ebx, 1
        mov ecx, temp
        mov edx, 1
        int 80h

    pop dword[temp]
    popad
    ret

read_word:


    pushad
    push dword[temp]

        read_word_loop:

            pushad
            mov eax, 3
            mov ebx, 0
            mov ecx, temp
            mov edx, 1
            int 80h

            popad
            
            mov al, byte[temp]
            cmp al, 32
            je read_word_loop_end
            cmp al, 10
            je read_word_loop_end_final
            stosb


        jmp read_word_loop

    read_word_loop_end:
        mov al,0 
        stosb

        mov byte[string_end], 0
        pop dword[temp]
        popad
        ret

    read_word_loop_end_final:
        mov al,0 
        stosb

        mov byte[string_end], 1
        pop dword[temp]
        popad
        ret




read_string:


    pushad
    push dword[temp]

        read_string_loop:

            pushad
            mov eax, 3
            mov ebx, 0
            mov ecx, temp
            mov edx, 1
            int 80h

            popad

            mov al, byte[temp]
            cmp al, 10
            je read_string_loop_end
            stosb


        jmp read_string_loop

    read_string_loop_end:
        mov al,0 
        stosb

        pop dword[temp]
        popad
        ret

print_string:
    pushad
    push dword[temp]
    print_sting_loop:
        lodsb

        cmp al, 0
        je print_string_loop_end
        mov byte[temp],al
        pushad

            mov eax, 4      
            mov ebx, 1      
            mov ecx, temp   
            mov edx, 1
            int 80h

        popad

    jmp print_sting_loop


    print_string_loop_end:

        pop dword[temp]
        popad
        ret


exit :
    mov eax, 1
    mov ebx, 0
    int 80h
    ret
