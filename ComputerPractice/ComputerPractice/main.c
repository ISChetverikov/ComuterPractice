#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

short int func_asm(char x, short int y, char z) {
	short int result = 0;
	_asm {

		mov al, x		// x в al
		cbw				// расширение до слова
		mov bx, 3d
		imul bx			// умножаем ax на 3
		dec ax			// уменьшаем ax на 1

		push ax			// сохраняем вычисленный знаменатель дроби в стэке

		mov al, z       // z в al
		cbw				// расширение до слова
		add ax, 7d		// в ax находится z + 7

		mov bx, 7d
		imul bx			// умножаем ax на 7

		mov bx, y		
		sub ax, bx		// вычитаем y

		pop bx			// достаем знаменатель из стэка
		
		idiv bx			// деление числителя на знаменатель

		add ax, 2d		// результат увеличиваем на 2

		mov result, ax	// результат заносим в ax
	}
	return result;
}

short int func(char x, short int y, char z) {
	return (7 * (z + 7) - y) / (3 * x - 1) + 2;
}

int main() {
	short int value_asm, value_c;

	setlocale(LC_CTYPE, "Russian");

	printf_s("========================\n");
	printf_s("Результаты выполнения:\n");
	printf_s("Первый тестовый набор:\n");
	value_asm = func_asm(0x1, 0x1, -0x8);
	value_c = func(0x1, 0x1, -0x8);
	printf("\tРезультат С: %X (16) или %d (10)\n", value_c, value_c);
	printf("\tРезультат Assembler: %X (16) или %d (10)\n", value_asm, value_asm);

	printf_s("Второй тестовый набор:\n");
	value_asm = func_asm(-0x6b, -0x3cf4, 0x74);
	value_c = func(-0x6b, -0x3cf4, 0x74);
	printf("\tРезультат С: %X (16) или %d (10)\n", value_c, value_c);
	printf("\tРезультат Assembler: %X (16) или %d (10)\n", value_asm, value_asm);
	
	printf_s("========================\n");

	return 0;
}

