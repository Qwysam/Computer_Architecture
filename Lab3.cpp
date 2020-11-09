//+===================================================================
// File Lab_3.cpp
// Ветвящаяся программа
// Вариант 4
// Эта программа вычисляет условное арифметическое выражение
// { a/b+10, a<b }
// Х = < -51, a=b >
// { (a*b-4)/a, a>b }
// где a=a/(4+2), b=b/(4+3)
//
// Выполняется проверка на переполнение
//
// (C) Жданов В.И., 2020
//-===================================================================
#include <stdio.h>
#include <locale.h>
#define VAR 4
long int a, a1, b, b1, x, x_a;
int err; // Ошибка в выражении на С
int err_a;// Ошибка в выражении на асcемблере
int main()
{
	setlocale(LC_ALL, "Russian");
	printf("\n\t\t(C) Жданов В.И., 2020");
	for (;;)
	{
		printf("\n\tВычислить выражение:");
		printf("\n\t { a/b+10, a<b }");
		printf("\n\tХ = < -51, a=b >");
		printf("\n\t { (a*b-4)/a, a>b }");
		printf("\n\tгде a=a/5, b=b/7");
		printf("\nПожалуйста, введите целые числа A и B : ");
		scanf_s("%li%li", &a, &b);
		//=============================== C ==================================
		// Разделить исходные переменные
		a1 = a / (VAR + 2);
		b1 = b / (VAR + 3);
		// Сбросить признак ошибки на С
		err = 0;
		// Вычислить выражение
		// a==b
		if (a1 == b1)
			x = -51;
		if (a1 < b1)
		{
			if (b1 == 0)
				err = 1;
			else
				x = a1 / b1 + 10;
		}
		if (a1 > b1) 
		{
			if (a1 == 0)
				err = 1;
			else
				x = (a1 * b1 - 4) / a1;
		}
		//============================ Assembler =============================
		// err_a=0; Нет ошибок
		__asm {
			mov err_a, 0
		}
		// Разделить исходные переменные на знаменатель VAR
		__asm {
			// b1=b/VAR+3
			mov ebx, VAR + 3
			mov eax, b
			cdq
			idiv ebx
			mov edi, eax // b1 -> edi
		   // a1=a/VAR+2
		   dec ebx
		   mov eax, a
		   cdq
		   idiv ebx // a1 -> eax
		}
		__asm {
			// Вычислить выражение
			// if (a1==b1)
			cmp eax, edi
			je Equal
			jl Less
			//if(a1>b1)
			Greater :
				// if (a1==0) err_a = 1
				test eax, eax
				je Error
				// else x = (a1*b1-4)/a1;
				imul edi, eax
				cdq
				sub edi, 4
				xchg eax,edi
				cdq
				idiv edi
				jmp Save
				//if(a1=b1)
			Equal :
				// x = -51;
				mov eax, -51
				jmp Save
				//if(a1<b1)
				//x = a1/b1+10
			Less :
				test edi, edi
				// if b1=0 err_a = 1
				je Error
				idiv edi //a1/b1-> eax
				add eax, 10
				cdq
			Save :
				mov x_a, eax // eax -> x
				jmp End
				// err_a = 1
			Error : // err = 1
				inc err_a
			End :
		}
		if (err==1)
			printf("***( C )*** Ошибка: попытка деления на 0\n");
		else
			printf("Результат ( C ): %li\n", x);
		if (err_a==1)
			printf("***(Asm)*** Ошибка: попытка деления на 0\n");
		else
			printf("Результат (Asm): %li\n", x_a);
	}

		return 0;
	}