#include <stdio.h> 
 
int main() {

	char x[4];

	printf("Please input four digits:\t");
	for (int i = 0; i < 4; i++)
	{
		x[i] = getc(stdin);
		if (x[i] < '0' || x[i] > '9') {
			printf_s("\nPlease input only digits!\n");
			return;
		}
	}

	__asm {

		mov al, x[0];
		sub al, 30h;
		mov bl, x[3];
		sub bl, 30h;

		mul bl;
		mov dx, ax;

		mov al, x[2];
		sub al, 30h;
		cbw;

		cmp dx, ax;
		jne ELSE;

		cmp ax, 7h;
		jg EXIT

		add x[2], 2;
		jmp EXIT
	
	ELSE:
		mov x[0], 39h;
		mov x[1], 39h;

	EXIT:
	}

	printf("\nResult:\t\t\t\t");
	for (int i = 0; i < 4; i++)
	{
		printf("%c", x[i]);
	}
	printf("\n");

	return 0;
}
