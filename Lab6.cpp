﻿//+===================================================================
// File lab6.cpp
// Упаковка битовых групп
//
// Эта программа упаковывает битовые группы в динное беззнаковое число
//
// (C)Жданов  В.И., 2020
//
// Входные данные:
// 7---6------0
// ! 0 ! mod  ! mod
// +---+------+
//		   7
// 15---11-----0
// ! 00 ! kop  ! kop
// +----+------+
//		  12
// 7----1-----0
// ! 00 ! w_b ! w_b
// +----+-----+
//	       2
// 7---6------0
// ! 0 ! reg1 ! reg1
// +---+------+
//		   7
// 7----3------0
// ! 00 ! reg2 ! reg2
// +----+------+
//		   4
//
// Выходные данные:
// Длинное целое беззнаковое число, которое содержит указанные битовые группы
//
// 31----+-----+-----+-----+-----0
// ! mod ! kop ! w_b ! reg1! reg2!	value
// +-----+-----+-----+-----+-----+
//	  7	   12	  2	    7	  4
//
//-===================================================================
#include <iostream>
#include <iomanip>
using namespace std;
unsigned char mod, w_b, reg1, reg2, mod_a, w_b_a, reg1_a, reg2_a;
unsigned short kop, kop_a;
unsigned long value, value_a;
unsigned short tmp;
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "\n\t\t(C) Жданов В.И., 2020"
		<< "\n\t\tРаспаковка битовых групп"
		<< "\n\tУпаковать битовые группы, содержащиеся в целых числах,"
		<< "\n\t\tв 32-битовое целое число Value";
	for (;;)
	{
		cout << "\nПожалуйста, введите 2 16-ые цифры для mod (например, 5a):";
		cin >> hex >> tmp; mod = tmp;
		cout << "Пожалуйста, введите 3 16-х цифры для kop (например, 9db):";
		cin >> kop;
		cout << "\nПожалуйста, введите 16-ую цифру для w_b (например, 3):";
		cin >> hex >> tmp; w_b = tmp;
		cout << "Пожалуйста, введите 2 16-х цифры для reg1 (например, 14):";
		cin >> hex >> tmp; reg1 = tmp;
		cout << "\nПожалуйста, введите 16-ую цифру для reg2 (например, a):";
		cin >> hex >> tmp; reg2 = tmp;
		// Сделать копии исходных чисел для фагмента на ассемблере
		mod_a = mod, kop_a = kop, w_b_a = w_b, reg1_a = reg1, reg2_a = reg2;
		//=============================== C ==================================
		// Очистить старшие биты в каждом исходном числе
		reg2 &= 0xf; // очистить все биты в числе, кроме 4 младших (3-0)
		reg1 &= 0x7f; // очистить все биты в числе, кроме 7 младших (10-4)
		w_b &= 0x3; // очистить все биты в числе, кроме 2 младших (12-11)
		kop &= 0xfff; // очистить все биты в числе, кроме 12 младших (24-13)
		mod &= 0x7f; // очистить все биты в числе, кроме 7 младших (31-25)
	   // Объединить каждое битовое поле с результирующим числом Value
		value = mod; // объединить поле mod с value
		value = (value << 12) | kop; // объединить поле kop с value
		value = (value << 2) | w_b; // объединить поле w_b с value
		value = (value << 7) | reg1; // объединить поле reg1 с value
		value = (value << 4) | reg2; // объединить поле reg2 с value
	   //============================ Assembler =============================
	   // Упаковать битовые группы
		__asm {
			// Очистить старшие биты в каждом исходном числе
			and mod_a, 0x7f
			and kop_a, 0xfff
			and w_b_a, 0x3
			and reg1_a, 0x7f
			and reg2_a, 0xf
			xor eax, eax
			// объединить поле mod с value
			or al, mod_a
			shl eax, 12
			// объединить поле kop с value
			or ax, kop_a
			shl eax, 2
			// объединить поле w_b с value
			or al, w_b_a
			shl eax, 7
			// объединить поле reg1 с value
			or al, reg1_a
			shl eax, 4
			// объединить поле reg2 с value
			or al, reg2_a
			mov value_a, eax
		};
		// Форматный вывод результатов
		cout << hex
			<< "Результирующее упакованное число (C++): " << value
			<< "\nРезультирующее упакованное число (Asm): " << value_a
			<< endl;
	};
	return 0;
}
