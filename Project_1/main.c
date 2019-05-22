#include <stdio.h>
#include "Polynom.h"

struct Polynom *GlobalPolynom;

void showMenu(){
    printf("Menu:\n");
    printf("\t1. Show polynom format\n");
    printf("\t2. Show current polynom\n");
    printf("\t3. Input polynom\n");
    printf("\t4. Calculate at point\n");
    printf("\t5. Derivative\n");
    printf("\t6. Close program\n");

    printf("\nChoose option: ");
}

void showFormat(){
    printf("\nInput polynom as: a0+a1*x+a1*x^2+...+an*x^n\n");
    printf("You can miss zero coefs and asterisk symbol (*)\n");
    printf("Example: 1+2x-3x^2+x^5+10x^14\n\n");
}

void calc(){
    double x;
    printf("Input number: ");
    scanf("%lf", &x);
    printf("Value at point: %lf", calcAtPoint(GlobalPolynom, x));
    printf("\n\n");
}

int main() {
    GlobalPolynom = newPoly(0, 0);

    int work = 1;

    while(work){
        showMenu();

        int option;
        scanf("%d", &option);

        switch (option){
            case 1:
                showFormat();
                break;

            case 2:
                showPoly(GlobalPolynom);
                break;

            case 3:
                inputPoly(GlobalPolynom);
                break;

            case 4:
                calc();
                break;

            case 5:
                printf("Not implemented\n");
                break;

            case 6:
                work = 0;
                break;

            default: break;
        }
    }

    cleanPoly(GlobalPolynom);
}