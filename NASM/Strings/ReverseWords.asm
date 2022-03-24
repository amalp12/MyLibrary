; 1. Write a program to read a sentence with n words, interchange 1st and nth
; words, 2nd and n-1th word etc.
; Example: input: country my is india, Output :India is my country

section .data
	msg1 db "Enter A Sentance : ", 10,0


section .bss
	
	string : resb 500
	str1 : resb 50
	temp : resd  1
	temp_word : resb 50
	temp_string : resb 500

section .text

	global _start:
		_start:
			mov eax, msg1
			call print_string
			mov eax, string

			call read_2D_sentance
            mov eax, string
            call interChangeWords
			call print_2D_sentance

			call exit

; eax should have the pointer to 2d string
interChangeWords:
	
        push dword[temp]
        pushad

        pushad
        ;find first and last pointer
        call numberOfWords
        ; eax has N
        sub eax, 1
    


        mov dword[temp], eax
        mov ebx, 50
        mul ebx

        mov dword[temp], eax

        popad
        mov ebx, eax
        add ebx, dword[temp]


        ; interchange ith and (n-1)th letter
        interChangeWordsLoop:
			cmp eax, ebx
			jge interChangeWordsLoopEnd

            pushad
            ; move eax string to temp_string
            mov ebx, temp_string
            mov ecx, 50
            call copyNBytes


            popad

            ; mov ebx sting to eax
            pushad
            push eax
            mov eax, ebx
            pop ebx
            mov ecx, 50
            call copyNBytes 
            popad


            ; move temp_string string to ebx
            pushad
            
            mov eax, temp_string
            
            mov ecx, 50
            call copyNBytes

            popad

			
			add eax, 50
			sub ebx, 50
			jmp interChangeWordsLoop

    interChangeWordsLoopEnd:
	    popad
	    pop dword[temp]
        ret

	

	
	
	
	

; eax had the 2d sentance pointer
print_2D_sentance:
	pushad
	push dword[temp]	
	
	
		
	print_2D_sentance_loop:
		cmp byte[eax], -1
		je print_2D_sentance_loop_end		
		push eax
		call print_string
		pop eax		
		add eax, 50
		call print_space
		jmp print_2D_sentance_loop

	print_2D_sentance_loop_end:
		
		pop dword[temp]
		popad 
		ret

; eax had the 2d sentance pointer
read_2D_sentance:
	pushad
	push dword[temp]	
	
	
		
	read_2D_sentance_loop:
		push eax
		call read_word
		pop eax		
			
		add eax, 50
		cmp ebx, 1
		je read_2D_sentance_loop_end
	jmp read_2D_sentance_loop

	read_2D_sentance_loop_end:
		mov byte[eax], -1
		pop dword[temp]
		popad 
		ret
read_word:
	pushad
	push dword[temp]	
	read_word_loop:
		push eax
		mov eax, 3
		mov ebx, 0
		mov ecx, temp
		mov edx, 1
		int 80h
		pop eax
		cmp byte[temp], 10
		je read_word_loop_end_sentance
		cmp byte[temp] , 32
		je read_word_loop_end

		mov dl, byte[temp]
		mov byte[eax], dl

		inc eax
	
		
		
		jmp read_word_loop

	read_word_loop_end:
		mov byte[eax], 0
		pop dword[temp]
		popad
		mov ebx, 0
		ret
	read_word_loop_end_sentance:
		mov byte[eax], 0
		pop dword[temp]
		popad
		mov ebx, 1
		ret
	

; string in eax, will get copied to string in ebx, N in ecx
copyNBytes:
	pushad
	push dword[temp]

	copyNBytes_loop:
		cmp ecx, 0
		je copyNBytes_loop_end
		mov dl, byte[eax]

		mov byte[ebx], dl
	
		inc eax,
		inc ebx
		dec ecx
		
		jmp copyNBytes_loop
	
	copyNBytes_loop_end:
		
		popad
		pop dword[temp]
		ret
	
	


; input eax strings pointer output number of words eax
numberOfWords:
    push dword[temp]
    pushad
    mov ecx, 0
    numberOfWordsLoop:
        cmp byte[eax], -1
        je numberOfWordsLoopEnd
        add eax, 50
        inc ecx
        jmp numberOfWordsLoop

    numberOfWordsLoopEnd:

	
        mov dword[temp], ecx
        popad
        mov eax, dword[temp]
        pop dword[temp]

        ret
	


; eax has the input string
; eax  will have the number 
largest_block:
	
	push dword[temp]
	pushad
	mov dword[temp],0 ; temp has the last max
	mov ecx, 0 ; ecx has the all time max
	mov dh, byte[eax]
	cmp dh, 0
	je largest_block_loop_end
	inc eax
	mov dword[temp],1 ; temp has the last max
	mov ecx, 1 ; ecx has the all time max
	largest_block_loop:
		mov dl, byte[eax]
		cmp dl, 0
		je largest_block_loop_end

		; if current same as prev increment count (temp)
		cmp dl,dh
		je inc_count
		jne reset_count
		reset_count_return:
		inc_count_return:
		inc eax
		mov dh, dl
		
		; if temp's value is greater than ecx then set new all time max
		cmp ecx, dword[temp]
		jl set_new_max
		set_new_max_return:
		

		jmp largest_block_loop
	set_new_max:
		mov ecx, dword[temp]
		jmp set_new_max_return  
	
	reset_count:
		mov dword[temp], 1
		jmp reset_count_return 
	inc_count:
		add dword[temp], 1
		jmp inc_count_return
	
	largest_block_loop_end:
		
		mov dword[temp], ecx
		add dword[temp], 30h
		mov eax, 4
		mov ebx, 1
		mov ecx, temp
		mov edx, 1
		int 80h 
	
		popad
		mov eax, dword[temp]
		pop dword[temp]
		
		ret

	

; eax has the string pointer
print_string:
	pushad
	push dword[temp]

	print_string_loop:
		mov dl, byte[eax]
		cmp dl , 0
		je print_string_loop_end
		mov byte[temp] , dl
		
		push eax
		mov eax, 4
		mov ebx, 1
		mov ecx, temp
		mov edx, 1
		int 80h
		pop eax
		inc eax
		
		
		jmp print_string_loop

	print_string_loop_end:
		
		pop dword[temp]	
		popad
		ret
	
;eax has the sting pointer
read_string:
	pushad
	push dword[temp]	
	read_string_loop:
		push eax
		mov eax, 3
		mov ebx, 0
		mov ecx, temp
		mov edx, 1
		int 80h
		pop eax
		cmp byte[temp], 10
		je read_string_loop_end

		mov dl, byte[temp]
		mov byte[eax], dl

		inc eax
	
		
		
		jmp read_string_loop

	read_string_loop_end:
		mov byte[eax], 0
		pop dword[temp]
		popad
		ret
print_newline:
	pushad
	push dword[temp]
	mov byte[temp],10
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
	mov byte[temp],32
	mov eax, 4
	mov ebx, 1
	mov ecx, temp
	mov edx, 1
	int 80h

	pop dword[temp]
	popad
	ret
	

exit:
	call print_newline 
	mov eax, 1
	mov ebx, 
