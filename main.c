#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359

typedef struct 
{
    double S, i0, k0;   
    int w;      
} 
MagnetParams;

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

int main() 
{
    system("chcp 65001");

    MagnetParams variants[3];

    FILE *fin = fopen("input.txt", "r");

    if (fin == NULL) 
    {
        printf("Не вдалося відкрити input.txt\n");
        return 1;
    }

    fscanf(fin, "%lf %lf %lf %lf", &T, &dt, &m, &n);
    for (int i = 0; i < 3; i += 1) 
    {
        fscanf(fin, "%lf %d %lf %lf", &variants[i].S, &variants[i].w, &variants[i].i0, &variants[i].k0);
    }
    fclose(fin);

    FILE *fout = fopen("result.txt", "w");
    if (fout == NULL) 
    {
        printf("Помилка при створенні файлу result.txt\n");
        return 1;
    }

    for (int v = 0; v < 3; v += 1) 
    {
        fprintf(fout, "=== Варіант %d ===\n", v + 1);
        fprintf(fout, "t\tF(t)\n");
        
        printf("=== Варіант %d ===\n", v + 1);
        printf("t\tF(t)\n");

        for (double t = 0.0; t <= T; t += dt) 
        {
            double I = get_I(t, variants[v].i0, variants[v].k0);
            double l = get_l(t);
            double F = get_F(I, variants[v].w, variants[v].S, l);

            fprintf(fout, "%.2f\t%.6f\n", t, F);
            printf("%.2f\t%.6f\n", t, F);
        }
        fprintf(fout, "\n");
        printf("\n");
    }

    fclose(fout);
    printf("Результати записано до result.txt\n");
    return 0;
}

