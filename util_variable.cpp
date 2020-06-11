//
// Created by 小田小田 on 2020/6/8.
//
#include "util_variable.h"

int GET_ID()
{
    static int id = 10000;
    return id++;
}

int COMPARE(double a, double b)
{
    if ((a-b) > 1e-6)
        return -1;
    else if ((b-a) > 1e-6)
        return 1;
    else
        return 0;
}

int COMPARE(double a) {
    if (a < 1e-6 && a > -1e-6)
        return 0;
    else
        return a>0?1:-1;
}
