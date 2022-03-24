
;2. Given a string, return the length of the largest "block" in the string. A block is
;a run of adjacent chars that are the same."
;Example:
;hoopla → 2
;abbCCCddBBBxx → 3

section .data
	msg1 db "Enter A Sentance : ", 10,0


section .bss
	
	string : resb 500
	temp : resd  1
section .text

	global _start:
		_start:
			mov eax, msg1
			call print_string
			mov eax, string

			call read_string

			call largest_block
			

			call exit


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

	

exit:
	call print_newline 
	mov eax, 1
	mov ebx, 0
	int 80h
	ret

