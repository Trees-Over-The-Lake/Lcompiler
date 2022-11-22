global _start
	section .data

M:
	resb 10000h
	section .text

_start:

section .data
		resd 1
section .text
		mov eax, 5
		mov [qword M + 0], eax
section .data
		resd 1
section .text
		mov eax, 3
		mov [qword M + 0], eax
		movss xmm0, [qword M + 65536]
		movss xmm1, [qword M + 65540]
		comiss xmm0, xmm1
		ja l 1
		mov al, 0
		jmp l2
		l1
		mov al, 1
		l2
		mov [qword M + 0], al
		mov al, [qword M + 0]
		cmp al, 0
		je l3
		mov eax, 10
		mov [qword M + 0], eax
		mov eax, [qword M + 65540]
		cdqe
		cvtsi2ss xmm0, rax
		movss xmm1, [qword M + 0]
		addss xmm1, xmm0
		movss [qword M + 0], xmm1
		mov rax, [qword M + 0]
		cvtsi2ss xmm0, rax
		movss [qword M + 0], xmm0
		jmp l4
		l3:
		mov eax, 253
		mov [qword M + 0], eax
		mov eax, [qword M + 0]
		cdqe
		cvtsi2ss xmm0, rax
		movss xmm1, [qword M + 0]
		addss xmm1, xmm0
		movss [qword M + 0], xmm1
		mov rax, [qword M + 0]
		cvtsi2ss xmm0, rax
		movss [qword M + 0], xmm0
		l4:
section .text
		mov rax,60
		mov rdi,0
		syscall
