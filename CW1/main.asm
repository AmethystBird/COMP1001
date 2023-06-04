.386  ; Specify instruction set
.model flat, stdcall  ; Flat memory model, std. calling convention
.stack 4096 ; Reserve stack space
ExitProcess PROTO, dwExitCode: DWORD  ; Exit process prototype

.data
	numberArray DWORD 10 DUP(?) ; declaration of array

.code
main PROC
	lea ebx, numberArray ; loads address of first element of array
	mov ecx, 2 ; stores divider and multiplier (since they are always the same value)
	mov esi, 0 ; stores the loop index
update: ; beginning of loop
	mov eax, [ebx + TYPE numberArray * esi] ; eax acquires the given array element

	add eax, esi ; adds the loop index (esi) to the value (eax)

	mul ecx ; multiplies eax by ecx and stores in eax
	add eax, 7 ; adds 7 to eax

	div ecx ; divides edi by ecx

	mov [ebx + Type numberArray * esi], eax ; moves new value into numberArray in its appropriate index

	inc esi ; increments the loop index by 1
	cmp esi, 10 ; ends the loop if the loop index hits the value of 10
	jne update

INVOKE ExitProcess, 0 ; call exit function

main ENDP ; exit main procedure
END main  ; stop assembling