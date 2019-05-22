//
// Created by ilya on 21.05.19.
//

#ifndef PROJECT_1_POLYNOM_H
#define PROJECT_1_POLYNOM_H

#endif //PROJECT_1_POLYNOM_H

struct Polynom{
    double coef;
    int power;

    struct Polynom *next_pow;
};

struct Polynom* newPoly(double coef, int power);
void addPow(struct Polynom *polynom, double coef, int power);
int isPow(struct Polynom *polynom, int power);

void setOrAdd(struct Polynom *polynom, double coef, int power);

void setCoef(struct Polynom *polynom, double coef, int power);
void showPoly(struct Polynom *p);

void cleanPoly(struct Polynom *p);
void inputPoly(struct Polynom *polynom);

double calcAtPoint(struct Polynom *p, double x);