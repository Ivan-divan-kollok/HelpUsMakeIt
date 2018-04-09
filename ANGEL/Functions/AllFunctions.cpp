#include "AllFunctions.h"

double _abs(double x)
{
    if (x < 0)
        return -x;
    return x;
}

double _max(double x, double y)
{
    if (x > y)
        return x;
    return y;
}

double _min(double x, double y)
{
    if (x < y)
        return x;
    return y;
}

double _sqr(double x)
{
    return x*x;
}

double _sqrt(double x)
{
    return sqrt(x);
}

int _round(double x)
{
    return (int) (x+0.5);
}

int _sgn(double x)
{
    if (x < 0)
        return -1;
    if (x > 0)
        return +1;
    return 0;
}
