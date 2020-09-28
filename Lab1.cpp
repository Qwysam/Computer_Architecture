//+===================================================================
// File lab_1.cpp
// Линейная арифметическая программа
// Вариант 4
// Эта программа проверяет арифметическое тождество (a-b)^3 = a^3-3a^2b+3ab^2+b^3,
//где a = a/6, b = b/7
//Для этого вычисляют значение левой и правой частей этого тождества
//на С и на ассемблере
//Жданов В.И.,26.09.2020
//-===================================================================
#include <iostream>
#include <math.h>
#include <string>
using namespace std;
//Определение макроконстанты варианта
# define DENOM 4
//Задание глобальных переменных
long int a, a1, b, b1, left_c, right_c, left_a, right_a;
int err, err_a;

int main(void)
{
    cout << "Input exit to stop the program\n";
    for (;;)
    {
        //Считывание переменных
        string input;
        cout << "Input a: ";
        cin >> input;
        if (input == "exit")
            break;
        a = stoi(input);
        //Вычисление выражения на C
        a1 = a / (DENOM + 2);
        cout << "Input b: ";
        cin >> b;
        b1 = b / (DENOM + 3);
        err = 0;
        left_c = (a1 - b1) * (a1 - b1) * (a1 - b1);
        right_c = a1 * a1 * a1 - 3 * a1 * a1 * b1 + 3 * a1 * b1 * b1 - b1 * b1 * b1;
        //Вычисление выражения на ассемблере
        _asm {
            //err_a=0
            mov err_a, 0

            //a1=a/DENOM+2
            mov ebx, DENOM + 2
            mov eax, a
            cdq
            idiv ebx
            mov esi, eax //esi = a

            //b1=b/DENOM+3
            mov ebx, DENOM + 3
            mov eax, b
            cdq
            idiv ebx
            mov edi, eax //edi = b

            //a-b
            mov eax, esi
            sub eax, edi
            mov ebx, eax // ebx = a-b
            //(a-b)*(a-b)*(a-b)
            imul eax, ebx
            jo Error
            imul eax, ebx
            jo Error
            mov left_a, eax

            // a * a * a - 3 * a * a * b + 3 * a * b * b - b * b * b
            mov eax, esi
            imul eax, esi
            jo Error
            imul eax, esi //a^3
            jo Error
            mov edx, edi //edx = b
            imul edx, esi //b*a
            jo Error
            imul edx, esi //b*a*a
            jo Error
            imul edx, 3 //edx = 3aab
            jo Error

            sub eax, edx //a^3 - 3aab

            mov edx, 3 // edx = 3
            imul edx, esi //3*a
            jo Error
            imul edx, edi //3ab
            jo Error
            imul edx, edi //3abb
            jo Error

            add eax, edx // + 3abb
            jo Error

            mov edx, edi // edx = b
            imul edx, edi //b*b
            jo Error
            imul edx, edi //b*b*b
            jo Error

            sub eax, edx // - b*b*b
            jo Error

            mov right_a, eax
            jmp End

            //overflow handling
            Error :
            mov err_a, 1

                End :
        };
        // Вывод вычислений на C
        cout << "Left: " << left_c << "\n";
        cout << "Right: " << right_c << "\n";
        //Проверка переполнения
        if (err_a)
            cout << "Overflow error\n";
        //Вывод вычислений на ассемблере 
        else {
            cout << "Left assembler: " << left_a << "\n";
            cout << "Right assembler: " << right_a << "\n";
        }
    }
    return 0;
}
