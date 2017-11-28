#include <stdio.h>
#include <locale.h>

int func_asm(char x, short int y, char z) {
	short int result = 0;
	_asm {
		xor eax, eax
		xor ecx, ecx
		xor edx, edx

		mov al, z       // z � al
		cbw				// ���������� �� �����
		add ax, 7d		// � ax ��������� z + 7

		imul ax, 7d     // �������� ax �� 7

		mov dx, y		// � � dx
		sub ax, dx		// �������� �� �������� � ax �������� y

		push ax			// ��������� ����������� ��������� ����� � �����

		mov al, x		// x � al
		cbw				// ���������� �� �����
		imul ax, 3d		// �������� ax �� 3
		dec ax			// ��������� ax �� 1

		pop cx			// ������� ��������� �� �����

		xchg cx, ax		// ����� ��������� � �����������

		cwd
		idiv cx			// ������� ��������� �� �����������

		add ax, 2d		// ��������� ����������� �� 2

		mov result, ax	// ��������� ������� � ax
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
	printf_s("���������� ����������:\n");
	printf_s("������ �������� �����:\n");
	value_asm = func_asm(0x1, 0x1, -0x8);
	value_c = func(0x1, 0x1, -0x8);
	printf("\t��������� �: %X (16) ��� %d (10)\n", value_c, value_c);
	printf("\t��������� Assembler: %X (16) ��� %d (10)\n", value_asm, value_asm);

	printf_s("������ �������� �����:\n");
	value_asm = func_asm(-0x6b, -0x3cf4, 0x74);
	value_c = func_asm(-0x6b, -0x3cf4, 0x74);
	printf("\t��������� �: %X (16) ��� %d (10)\n", value_c, value_c);
	printf("\t��������� Assembler: %X (16) ��� %d (10)\n", value_asm, value_asm);
	
	printf_s("========================\n");


	return 0;
}

