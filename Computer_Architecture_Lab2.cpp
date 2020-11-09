//+===================================================================
// File lab_2.cpp
// Линейная логическая программа
// Вариант 4
// Эта программа вычисляет три логические функции
//
// F1(x3,x2,x1,x0)=(3,4,5,6,7,8,9)
// F2(x3,x2,x1,x0)=(8,9,10,11,12,13)
// F3(x3,x2,x1,x0)=(2,3,4,5,6)
//
// (C) Жданов В.И., 2020
//-===================================================================
#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;
bool x3, x2, x1, x0, f1, f2, f3, f1_a, f2_a, f3_a;
int main()
{
	setlocale(LC_ALL, "Russian");
	printf("\n\t(C) Жданов В.И., 2020");
	printf("\n\tВычислить значение логических функций:");
	printf("\n\tF1(x3,x2,x1,x0)=(3,4,5,6,7,8,9)");
	printf("\n\tF2(x3,x2,x1,x0)=(8,9,10,11,12,13)");
	printf("\n\tF3(x3,x2,x1,x0)=(2,3,4,5,6))");
	for (;;)
	{
		printf("\nПожалуйста, введите булевы переменные x3, x2, x1, x0: ");
		cin >> x3 >> x2 >> x1 >> x0;
		//=============================== C ==================================
		f1 = (!x3&&x2)||(x0&&x1&&!x3)||(x3&&!x2&&!x1);
		f2 = x3 && (!x2 || !x1);
		f3 = !x3&&(x1&&!x2||x2&&(!x1||!x0));
		//============================ Assembler =============================
		// Вычислить функцию F1 = (!x3&&x2)||(x0&&x1&&!x3)||(x3&&!x2&&!x1)
			__asm {
			// (!x3&&x2)||(x0&&x1&&!x3)||(x3&&!x2&&!x1)->al
			// (!x3&&x2)->al
			mov al, x3
			not al
			and al,x2
			// (x0&&x1&&!x3)->ah
			mov ah, x3
			not ah
			and ah, x1
			and ah, x0
			//(!x3&&x2)||(x0&&x1&&!x3)->al
			or al, ah
			// (x3&&!x2&&!x1)->ah
			mov ah, x2
			not ah
			mov bl, x1
			not bl
			and ah,bl
			and ah,x3
			// ah||al->f1_a
			or al, ah
			and al, 1
			mov f1_a, al
			};
			__asm {
				// Вычислить функцию F2=x3 && (!x2 || !x1)
				// !x2->al
				mov al, x2
				not al
				// !x1->ah
				mov ah, x1
				not ah
				// al||ah->al
				or al, ah
				// x3&&al->f2_a
				and al,x3
				and al, 1
				mov f2_a, al
			};
			// Вычислить функцию F3 = !x3&&(x1&&!x2||x2&&(!x1||!x0))
			__asm {
				// !x0->al
				mov al, x0
				not al
				// !x1->ah
				mov ah, x1
				not ah
				// al||ah->al
				or al, ah
				// x2->ah
				mov ah, x2
				// al&&ah->al
				and al, ah
				//!x2&&x1->ah
				not ah
				and ah, x1
				//al||ah->al
				or al, ah
				//!x3->ah
				mov ah, x3
				not ah
				// al&&ah->f3_a
				and al,ah
				and al, 1
				mov f3_a, al
			};
			// Вывод результатов
			int i, j, k, l, m;
			// Преобразовать булевы переменные в двоичные цифры
			i = (int)x3; j = (int)x2; k = (int)x1; l = (int)x0;
			// Преобразовать четыре двоичные цифры в двоичный код
			m = (i << 3) + (j << 2) + (k << 1) + l;
			// Форматный вывод результатов
			cout << "               ___C++__  ___Asm__" << endl
				 << "Набор" << " " << setw(2) << "x3" << "x2" << "x1" << "x0"
				 << " " << "F1 " << "F2 " << "F3 "
				 << " " << "F1 " << "F2 " << "F3 " << endl;
			cout << "  " << setw(2) << m << " " << " " << i << " " << j << " " << k << " " << l
				 << "  " << f1 << "  " << f2 << "  " << f3
				 << "   " << f1_a << "  " << f2_a << "  " << f3_a << endl;
	}
	return 0;
}