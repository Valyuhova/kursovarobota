#ifndef LOGIC_H
#define LOGIC_H

typedef struct 
{
    double S, i0, k0;   
    int w;      
} 
MagnetParams;

extern double T, dt, m, n;
extern const double l0;

double get_k(double t, double k0);
double get_I(double t, double i0, double k0);
double get_l(double t);
double get_F(double I, int w, double S, double l);

#endif
