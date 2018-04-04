#include <stdio.h> 
 
int main() {

	char x1 = 0, x2 = 0, x3 = 0, x4 = 0;

	printf("Please input four digits:\t");
	x1 = getc(stdin);
	x2 = getc(stdin);
	x3 = getc(stdin);
	x4 = getc(stdin);

	__asm {

		mov al, x1;
		sub al, 30h;
		mov bl, x4;
		sub bl, 30h;

		mul bl;
		mov dx, ax;

		mov al, x3;
		sub al, 30h;
		cbw;

		cmp dx, ax;
		jne ELSE;

		cmp ax, 7h;
		jg EXIT

		add x3, 2;
		jmp EXIT
	
	ELSE:
		mov x1, 39h;
		mov x2, 39h;

	EXIT:
	}

	printf("\nResult:\t\t\t\t");
	printf("%c%c%c%c\n\n", x1, x2, x3, x4);
	return 0;
}
