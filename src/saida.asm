global _start
	section .data

M:
	resb 10000h
	section .text

_start:

section .data
		resb 1
section .text
		mov al,  τύ
		mov [qword M + 65536], eax
section .data
		resb 1
section .text
		mov al,  τύ
		mov [qword M + 65537], eax
