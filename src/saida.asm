global _start
	section .data

M:
	resb 10000h
section .text

_start:

section .data
		resd 1
section .text
		mov eax, 10
		mov [qword M + 0], eax
section .data
		resd 1
section .text
		mov eax, 5
		mov [qword M + 4], eax
		mov eax, [qword M + 0]
		mov ebx, [qword M + 4]
		cmp eax, ebx
		jb l1
		mov al, 0
		jmp l2
	l1:
		mov al, 1
	l2:
		mov [qword M + 8], al
	l3:
		mov al, [qword M + 4]
		cmp [qword M + 0], al
		je l4
		mov ax, 1
		mov eax, 1
		mov [qword M + 9], eax
		mov eax, [qword M + 4]
		mov ebx, [qword M + 9]
		add eax, ebx
		mov [qword M + 13], eax
		mov eax, [qword M + 13]
		mov [qword M + 4], eax
		jmp l3
	l4:
		mov eax, [qword M+4]
		mov rsi, M+0
		mov rcx, 0
		mov rdi, 0
		cmp eax, 0
		jge l5
		mov bl, '-' 
		mov [rsi], bl
		add rsi, 1
		add rdi, 1
		neg eax
	l5:
		mov ebx, 10
	l6:
		add rcx, 1
		cdq
		idiv ebx
		push dx
		cmp eax, 0
		jne l6
		add rdi,rcx
	l7:
		pop dx
		add dl, '0'
		mov [rsi], dl
		add rsi, 1
		sub rcx, 1
		cmp rcx, 0
		jne l7
		mov rsi, M+0
		mov rax, 1
		mov rdi, 1
		syscall
		mov al, 0Ah
		mov [qword M + 256], al
		mov rsi, M + 256
		mov rdx, 1
		mov rax, 1
		mov rdi, 1
		syscall
section .text
		mov rax,60
		mov rdi,0
		syscall
