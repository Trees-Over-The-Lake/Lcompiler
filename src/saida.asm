global _start
	section .data

M:
	resb 10000h
section .text

_start:

section .data
		resb 100h
section .text
		mov rsi, M + 65536
		mov rax, 0
		mov rdi, 0
		mov rdx, 100h
		syscall
		mov byte [M+65536+rax-1], 0
section .data
		db "Hello ",0
section .text
		mov rsi, M + 65543
		mov rdx, 100h
		mov rax, 1
		mov rdi, 1
		syscall
		mov rsi, M + 65536
		mov rdx, 100h
		mov rax, 1
		mov rdi, 1
		syscall
		mov al, 0Ah
		mov [qword M + 0], al
		mov rsi, M + 0
		mov rdx, 1
		mov rax, 1
		mov rdi, 1
		syscall
section .text
		mov rax,60
		mov rdi,0
		syscall
