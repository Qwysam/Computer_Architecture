//+===================================================================
// File lab_7.cpp
// Циклическая программа, работающая с массивом
// Вариант 4
// Программа выполняет сортировку простым выбором
// Длина масива и сам массив вводятся из файла in.txt
//
// (C) Жданов В.И., 2020
//-===================================================================
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define MAX_LENGTH 100
long int arr[MAX_LENGTH], arr_a[MAX_LENGTH];
int len;
int main()
{
	setlocale(LC_ALL, "Russian");
	int i, j, tmp;
	FILE *fin;
	errno_t err;
	printf("\n\t\t(C) Жданов В.И., 2020\n");
	// Открыть файл с исходными данными
	if ((fin = fopen("in.txt", "r")) == NULL)
	{
		printf("\nCan't open file\n"); 
		exit(1);
	}

	for (;;)
	{
		// Читать длину масива
		fscanf_s(fin, "%i\n", &len);
		// Если массив имеет ненулевую и допустимую длину, читать его
		if (len == 0 || len > 100) 
			break;
		// Копировать файл в массив
		for (i = 0; i < len; i++) fscanf_s(fin, "%i", &arr[i]);
		// Сделать копию для ассемблера
		for (i = 0; i < len; i++) arr_a[i] = arr[i];
		printf("\n\tСортировка массива простым выбором");
		//=============================== C ==================================
		// Вывод исходного массива
		printf("\nИсходный масив имеет длину: %i\n", len);
		for (i = 0; i < len; i++) printf("%8i", arr[i]);
		// Перенос отрицательных элементов в конец массива
		for (i = 0; i < len - 1; i++)

			// Last i elements are already in place  
			for (j = 0; j < len - i - 1; j++)
				if (arr[j] < 0) 
				{
					int tmp = arr[j + 1];
					arr[j + 1] = arr[j];
					arr[j] = tmp;
				}
		// Вывод результирующего массива
		printf("\nРезультирующий массив ( C )\n");
		for (i = 0; i < len; i++) printf("%8i", arr[i]);
		//============================ Assembler =============================
		__asm {
			// for (i=0; i<len; i++)
			xor esi, esi// i = 0
			mov ecx, len
			mov edx, 0
		L0 :
			cmp esi, ecx // проверка условия i<len
			//завершить,если i>=len
			jnl End
			// if(arr[i]<0) {
			cmp [arr_a + esi * 4],0
			jl L1

			inc esi //i++
			jmp L0

		//arr[i]<0
		L1 :
			//for(j=tmp; j>0; j--)
			mov edi, esi //j=i
		L2 :
			cmp edi, 0 // j>0
			jng L3
			mov eax, [arr_a + edi * 4 - 4]
			mov[arr_a + edi * 4], eax
			dec edi
			jmp L2
		L3 :
			mov[arr_a + edx * 4], ebx
			inc edx
			inc esi
			jmp L0
		End :
		};
		// Вывод результатов
		printf("\nРезультирующий массив (Asm)\n");
		for (i = 0; i < len; i++) printf("%8i", arr[i]);
		printf("\n");
		break;
	}
	fclose(fin);// Закрыть исходный файл
	return 0;
}