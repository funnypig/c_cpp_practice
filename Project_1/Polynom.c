//
// Created by ilya on 21.05.19.
//

// if the polynom is 2x-x^2
// i represent it by to structures: (coef=2, power=1) and (coef=-1, power=2)
// and (coef=-1, power=2) is next_pow for (coef=2, power=1)


#include "stdio.h"
#include "stdlib.h"
#include "Polynom.h"


// FUNCTIONS TO MANIPULATE POLYNOMS

struct Polynom* newPoly(double coef, int power){

    struct Polynom *p = malloc(sizeof(struct Polynom));

    p->coef = coef;
    p->power = power;
    p->next_pow = 0;

    return p;
}

void addPow(struct Polynom *polynom, double coef, int power){
    struct Polynom *copy = polynom;

    while(1){
        if (copy->next_pow == 0){
            copy->next_pow = newPoly(coef, power);
            break;
        }else{
            copy = copy->next_pow;
        }
    }
}

int isPow(struct Polynom *polynom, int power){
    /*
     * returns 1 if there is such power in polynom, 0 otherwise
     */

    if (polynom == 0){
        return 0;
    }

    struct Polynom* copy = polynom;

    while(copy!=0){
        if (copy->power == power){
            return 1;
        }
        copy = copy->next_pow;
    }

    return 0;
}

void setCoef(struct Polynom *p, double coef, int power){
    // Set coef in polynom to power

    /*
     * F.e. p = 1+x+x^2
     * -> setCoef(p, -5, 1) => p = 1-5x+x^2
     *
     * do nothing if there is not such power
     */

    if (p == 0){
        return;
    }

    struct Polynom *copy = p;

    while(copy!=0){
        if (copy->power == power){
            copy->coef = coef;
            return;
        }

        copy = copy->next_pow;
    }
}

void setOrAdd(struct Polynom *polynom, double coef, int power){
    if (isPow(polynom, power)){
        setCoef(polynom, coef, power);
    }else{
        addPow(polynom, coef, power);
    }
}

void showPoly(struct Polynom *p){
    struct Polynom *copy = p;

    printf("\n");
    while (copy!=0){
        if (copy->coef < 0){
            printf("%.3f*x^%d",copy->coef, copy->power);
        }else{
            printf("+%.3f*x^%d",copy->coef, copy->power);
        }

        copy = copy->next_pow;
    }
    printf("\n\n");
}

void cleanPoly(struct Polynom *p){
    if (p->next_pow == NULL){
        free(p);
    }else{
        cleanPoly(p->next_pow);
        free(p);
    }
}

double power(double x, int power){
    double res = 1;
    for (int i = 0; i<power; i++){
        res*=x;
    }
    return res;
}

double calcAtPoint(struct Polynom *p, double x){
    struct Polynom *copy = p;
    double res = 0;

    while(copy){
        res += copy->coef * power(x, copy->power);

        copy = copy->next_pow;
    }

    return res;
}

void inputPoly(struct Polynom* polynom){
    printf("Existing polynom will be updated!\n");
    printf("Enter polynom in required format (max len = 1000):\n");
    char sp[1000];
    scanf("%s", sp);

    int index = -1; // sorry for that, just comfortable

    int curCoef = 0;
    int curPower = 0;
    int curSign = 1;

    int enteringIndicator = 0; // 0 - reading coef, 1 - reading power
    int atLeastFirstPower = 0;

    while (1){
        index++;

        char curchar = sp[index];
        if (curchar == '\n' || curchar == 0) break;
        if (curchar == ' ') continue;

        // STRING JUST STARTED OR POWER HAS FINISHED
        // REMEMBER SIGN AND WRITE REMEMBERED COEF AND POWER
        if (curchar == '-'){

            if (curCoef != 0){
                // I DIDNT CALCULATE power=1 if there is poly: 2x
                if (curPower == 0 && atLeastFirstPower){
                    curPower = 1;
                }

                setOrAdd(polynom, curCoef * curSign, curPower);
            }

            curCoef = 0;
            curPower = 0;
            curSign = -1;
            atLeastFirstPower = 0;
            enteringIndicator = 0;
            continue;
        }
        if (curchar == '+'){

            if (curCoef != 0){
                if (curPower == 0 && atLeastFirstPower){
                        curPower = 1;
                }

                setOrAdd(polynom, curCoef * curSign, curPower);
            }

            curCoef = 0;
            curPower = 0;
            curSign = 1;
            atLeastFirstPower = 0;
            enteringIndicator = 0;
            continue;
        }

        if (curchar == '*' || curchar == 'x'|| curchar == '^'){
            enteringIndicator = 1;
            atLeastFirstPower = 1;
            continue;
        }

        if (enteringIndicator == 0){
            curCoef = curCoef * 10 + (curchar-48);
        }else{
            curPower = curPower * 10 + (curchar-48);
        }
    }

    if (curPower == 0 && atLeastFirstPower){
        curPower = 1;
    }
    if (curCoef != 0){
        setOrAdd(polynom, curCoef * curSign, curPower);
    }
}

