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
#define MAX_LENGTH 100
long int arr[MAX_LENGTH], arr_a[MAX_LENGTH];
int len;
int main()
{
	setlocale(LC_ALL, "Russian");
	int i, j;
	FILE *fin;
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
		{
			// Last i elements are already in place  
			for (j = 0; j < len; j++)
				if (arr[j] < 0)
				{
					if (arr[j + 1] > 0)
					{
						int tmp = arr[j + 1];
						arr[j + 1] = arr[j];
						arr[j] = tmp;
					}
				}
		}
		// Вывод результирующего массива
		printf("\nРезультирующий массив ( C )\n");
		for (i = 0; i < len; i++) printf("%8i", arr[i]);
		//============================ Assembler =============================
		__asm {
				//for (i=0 i<len i++)
				xor esi, esi
				mov    ecx, len
				//for (j=0 j<=len j++) { 
			L0 :
				mov edi, 0
				L1 :
				//    tmp = arr[j]
				mov    eax, arr_a[edi * 4]
				//    if(arr[j]<0) {
				cmp eax, 0
				jge L2
				//    if(arr[j+1]<0) {            
				cmp arr_a[edi * 4 + 4], 0
				jng L2
				//    arr[j] = arr[j + 1]
				xchg eax, arr_a[edi * 4 + 4]
				//    arr[j] = tmp}
				xchg eax, arr_a[edi * 4]
			L2:
				inc edi
				cmp    edi, ecx
				jle    L1
				inc    esi
				cmp    esi, ecx
				jl    L0
		};
		// Вывод результатов
		printf("\nРезультирующий массив (Asm)\n");
		for (i = 0; i < len; i++) printf("%8i", arr_a[i]);
		printf("\n");
	}
	fclose(fin);// Закрыть исходный файл
	return 0;
}