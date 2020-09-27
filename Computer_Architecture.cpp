#include <iostream>
#include <math.h>
#include <string>
using namespace std;

# define DENOM 4

long int a, a1, b, b1, left_c, right_c, left_a, right_a;
int err, err_a;

int main(void)
{
    cout << "Input exit to stop the program\n";
    for (;;)
    {
        string input;
        cout << "Input a: ";
        cin >> input;
        if (input == "exit")
            break;
        a = stoi(input);
        a1 = a / (DENOM + 2);
        cout << "Input b: ";
        cin >> b;
        b1 = b / (DENOM + 3);
        err = 0;
        left_c = (a - b) * (a - b) * (a - b);
        right_c = a * a * a - 3 * a * a * b + 3 * a * b * b - b * b * b;
        _asm {
            //err_a=0
            mov err_a, 0

            //a1=a/DENOM+2
            mov ebx, DENOM+2
            mov eax, a
            cdq
            idiv ebx
            mov esi, eax //esi = a

            //b1=b/DENOM+3
            mov ebx, DENOM+3
            mov eax, b
            cdq
            idiv ebx
            mov edi, eax //edi = b

            //a-b
            mov eax, esi
            sub eax,edi
            //(a-b)*(a-b)*(a-b)
            imul eax,eax
            imul eax,eax
            jo Error
            mov left_a, eax

            // a * a * a - 3 * a * a * b + 3 * a * b * b - b * b * b
            mov eax, esi
            imul eax,eax
            imul eax,eax //a^3
            mov edx, edi //edx = b
            imul edx, esi //b*a
            imul edx, esi //b*a*a
            imul edx, 3 //edx = 3aab
            jo Error

            sub eax,edx //a^3 - 3aab

            mov edx, 3 // edx = 3
            imul edx, esi //3*a
            imul edx, edi //3ab
            imul edx, edi //3abb
            jo Error

            add eax, edx // + 3abb

            mov edx, edi // edx = b
            imul edx, edx //b*b
            imul edx, edx //b*b*b
            jo Error

            sub eax, edx // - b*b*b

            mov right_a, eax


            //overflow handling
            Error:
            mov err_a, 1

        }
        cout << "Left: " << left_c << "\n";
        cout << "Right: " << right_c << "\n";
        cout << "Left assembler: " << left_a << "\n";
        cout << "Right assembler: " << right_a << "\n";
    }
    return 0;
}