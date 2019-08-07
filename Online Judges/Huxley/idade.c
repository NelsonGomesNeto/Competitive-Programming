#include <stdio.h>

int main()
{
    float num, media = 0, divi = 0;
    while (scanf("%i", &num)&& num >= 0)
    {
        divi ++;
        media += num;
    }
    if (divi > 0)
    {
        media /= divi;
    }
    printf("%.2f\n", media);
    return(0);
}