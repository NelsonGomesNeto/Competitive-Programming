#include <stdio.h>

int main()
{
    int tam;
    scanf("%d", &tam);

    switch(tam)
    {
        case 3:
            printf("Equilatero\n");
            break;
        case 4:
            printf("Quadrado\n");
            break;
        case 5:
            printf("Pentagono\n");
            break;
        case 6:
            printf("Hegaxono\n");
            break;
        case 7:
            printf("Heptagono\n");
            break;
        case 8:
            printf("Octogono\n");
            break;
        case 9:
            printf("Eneagono\n");
            break;
        case 10:
            printf("Decagono\n");
            break;
        default:
            printf("Digite inteiros entre 3 e 10\n");
    }

    return 0;
}
