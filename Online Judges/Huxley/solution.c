#include <stdio.h>

int main() {
    int i,j,linhas,colunas, invalida  = 0;
    scanf("%d%d", &linhas, &colunas);
    int matriz[linhas][colunas];
    for (i = 0; i < linhas; i++)
        for (j = 0; j< colunas; j++)
            scanf("%d", &matriz[i][j]);
    int minzero = 0;
    for (j = 0; j < colunas; j++) {
        if (matriz[0][j] != 0)
            break;
        minzero++;
    }
    int qtzeros = 0;
    for (i = 1; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            if (matriz[i][j] != 0)
                break;
            qtzeros++;
        }
        if (qtzeros <= minzero && qtzeros!=colunas) {
            invalida = 1;
            break;
        }
        minzero = qtzeros;
        qtzeros = 0;

    }
    if (invalida)
        printf("N\n");
    else
        printf("S\n");
    return 0;
}
