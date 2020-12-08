//+===================================================================
// File lab_5.cpp
// Вариант 4
// Задание:  Эта программа вычисляет арифметическое выражение при помощи сдвигов
//
//     Z = x*a/b
//
//     V = y*a/b
//
//
//  Жданов В.И. 2020
//-===================================================================

#include <stdio.h>
#include <iostream>

using namespace std;

unsigned int x, Z, Z_A;

int y, V, V_A;

int error = 0;
int main()
{
    setlocale(LC_ALL, "Russian");
    printf("Умножение и деление беззнакового и знакового \nцелого числа на константу\n");
    for (;;)
    {
        // 53/4
        // Num = x* 53 / 4 = (32x + 16x + 4x + x) / 4
        // unsigned int input
        printf("x :");
        scanf_s("%ui", &x);
        //int input
        printf("y :");
        scanf_s("%i", &y);
        Z = ((x << 5) + (x << 4) + (x << 2) + (x)) >> 2;


        V = ((y << 5) + (y << 4) + (y << 2) + (y)) >> 2;
        //unsigned calculation
        __asm {
            mov     error, 0
            mov     edx, x       //edx <= x
            mov     ebx, edx     //ebx <= x
            mov     eax, edx     //edx <= x

            shl     eax, 5       //32x
            jc      Error

            shl     ebx, 4       //16x
            jc      Error

            add     eax, ebx     //32x+16x
            jc      Error

            add     eax, edx     //32x+16x + x
            jc      Error

            shl     edx, 2       //4x
            jc      Error

            add     eax, edx     //32x+ 16x + 4x + x (eax)
            jc      Error

            shr     eax, 2       //(32x+ 16x + 4x + x)/4
            mov     Z_A, eax     //eax => Z_A

            jmp     End

    Error :
            inc error
    End :
        };
        //error handling
        if (error == 1)
        {
            printf("\t\tError CF \n");
        }
        //result output
        printf("Unsigned decimal number  C++(Z):\t[%u]", Z);
        printf("\tUnsigned decimal number  Asm (Z_A):\t[%u]\n\n", Z_A);
        //signed calculation
        __asm {
            mov     error, 0
            mov     edx, y       //edx <= x
            mov     ebx, edx     //ebx <= x
            mov     eax, edx     //edx <= x

            sal     eax, 5       //32x
            jo      Error2

            sal     ebx, 4       //16x
            jo      Error2

            add     eax, ebx     //32x+16x
            jo      Error2

            add     eax, edx     //32x+16x + x
            jo      Error2

            sal     edx, 2       //4x
            jo      Error2

            add     eax, edx     //32x+ 16x + 4x + x (eax)
            jo      Error2

            sar     eax, 2       //(32x+ 16x + 4x + x)/4

            mov     V_A, eax     //eax => Z_A

            jmp     End2

Error2 :
            inc error
End2 :
        };
        //error handling
        if (error == 1)
        {
            printf("\t\tError OF \n");
        }
        //result output
        printf("Signed decimal number  C++(V) :\t\t[%d]", V);
        printf("\tSigned decimal number Asm(V_A) :\t[%d]\n\n", V_A);
    }

}