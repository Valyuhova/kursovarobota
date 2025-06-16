#include <math.h>
#include "logic.h"

#define PI 3.14159265359

double T, dt, m, n;
const double l0 = 1.0;

double get_k(double t, double k0) 
{
    if (t <= T / 2.0)
    {
        return k0 * (1 - exp(-m * t));
    }

    else
    {
        return k0 * (1 - exp(-m * T / 2.0));
    }  
}

double get_I(double t, double i0, double k0) 
{
    double k = get_k(t, k0);

    if (t <= T / 8.0)
    {
        return i0 * (1 + k * t);
    }

    else if (t <= 3 * T / 8.0)
    {
        return i0 * (1 + k * T / 8.0);
    }

    else if (t <= 5 * T / 8.0)
    {
        return i0 * (1 + k * T / 8.0 - k * (t - 3 * T / 8.0));
    }

    else if (t <= 7 * T / 8.0)
    {
        return i0 * (1 - k * T / 8.0);
    }

    else
    {
        return i0 * (1 - k * T / 8.0 + k * (t - 7 * T / 8.0));
    }
}

double get_l(double t) 
{
    if (t <= T / 4.0)
    {
        return l0 * (1 + n * t);
    }

    else
    {
        return l0 * (1 + n * T / 4.0);
    }
}

double get_F(double I, int w, double S, double l) 
{
    double numerator = pow(0.4 * PI * I * w, 2) * S * 1e-4;
    double denominator = 8.0 * PI * l * l;
    return 1e-5 * numerator / denominator;
}
