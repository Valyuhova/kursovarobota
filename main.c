#include <stdio.h>
#include <stdlib.h>
#include "logic.h"

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



