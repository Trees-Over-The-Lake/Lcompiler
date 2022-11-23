global _start
	section .data

M:
	resb 10000h
	section .text

_start:

section .data
		resb 1
section .text
		mov al, 1
		mov [qword M + 0], al
section .data
		resb 1
section .text
		mov al, 0
		mov [qword M + 0], al
		mov eax, [qword M + 65537]
		mov ebx, [qword M + 65536]
		imul ebx
		mov [qword M + 0], eax
		mov al, [qword M + 65536]
		cmp al, 0
		je l1
		mov al, false
		mov [qword M + 0], eax
		mov al, [qword M + 0]
		mov [qword M + 65536], al
		l1:
section .text
		mov rax,60
		mov rdi,0
		syscall
