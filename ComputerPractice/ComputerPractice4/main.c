#include <stdlib.h>
#include <stdio.h>

#define SIZE 16

int main()
{
	char A[SIZE] = { 1, -23, -87, 5, 9, 7, -121, 129, 23, 10, -7 , 9, -2, -56, 56, 67};
	char B[SIZE - 1];
	char* C[SIZE - 1];

	char l = sizeof(B);
	char count = 0;

	printf("\nArray A (%d): \n", count);
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d\t", A[i]);
	}

	_asm {
		push l;
		lea esi, A;
		lea edi, B;
		lea edx, C;
		pop cl;

	LOOP2:

		mov al, [esi];
		inc esi;
		mov bl, [esi];

		sub bl, al;
		cmp bl, 0;
		jge NOT_NEGATIVE;

		mov bl, 0;
		inc count;

		mov [edx], edi;
		add edx, 4;

	NOT_NEGATIVE:
		mov [edi], bl;
		inc edi;

		dec cl;
		cmp cl, 0;
		jne LOOP2;
	}

	printf("\n\nArray B (%d): \n", count);
	for (int i = 0; i < l; i++)
		printf("%d\t", B[i]);

	printf("\n\nArray C: \n");
	for (int i = 0; i < count; i++)
		printf("%p\t", C[i]);

	printf_s("\n");
	return 0;
}
