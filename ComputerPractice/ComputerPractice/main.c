#include <stdio.h>
#include <locale.h>

int func_asm(char x, short int y, char z) {
	short int result = 0;
	_asm {
		xor eax, eax
		xor ecx, ecx
		xor edx, edx

		mov al, z       // z в al
		cbw				// расширение до слова
		add ax, 7d		// в ax находится z + 7

		imul ax, 7d     // умножаем ax на 7

		mov dx, y		// у в dx
		sub ax, dx		// вычитаем из значения в ax значение y

		push ax			// сохраняем вычисленный числитель дроби в стэке

		mov al, x		// x в al
		cbw				// расширение до слова
		imul ax, 3d		// умножаем ax на 3
		dec ax			// уменьшаем ax на 1

		pop cx			// достаем числитель из стэка

		xchg cx, ax		// обмен числителя и знаменателя

		cwd
		idiv cx			// деление числителя на знаменатель

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
	value_c = func_asm(-0x6b, -0x3cf4, 0x74);
	printf("\tРезультат С: %X (16) или %d (10)\n", value_c, value_c);
	printf("\tРезультат Assembler: %X (16) или %d (10)\n", value_asm, value_asm);
	
	printf_s("========================\n");


	return 0;
}

