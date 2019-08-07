#include <stdio.h>
#include <stdlib.h>

int** alocaMatriz(int n, int m){
	int i;
	int** matriz = (int**)calloc(n, sizeof(int*));
	for (i = 0; i < n; i++){
		matriz[i] = (int*)calloc(m, sizeof(int));
	}
	return matriz;
}

void liberaMatriz(int** matriz, int n, int m){
	int i;
	for (i = 0; i < n; i++){
		free(matriz[i]);
	}
	free(matriz);
}


void leMatriz(int** matriz, int n, int m){
	int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j < m; j++){
			scanf("%1d", &matriz[i][j]);
		}
	}
}

void Analizer(int** matriz, int li, int lf, int ci, int cf, int* cont){
	int i, j, desigual = 0;

	for (i = li; i <= lf; i++){
		for (j = ci; j <= cf; j++){
			if (matriz[i][j] != matriz[li][ci]){
				desigual = 1;
			}
		}
	}

	if (*cont == 50){
		printf("\n");
		*cont = 0;
	}

	if (desigual){
		printf("D");
		(*cont)++;
		if (lf - li && cf - ci){
			Analizer(matriz, li, (li + lf) / 2, ci, (ci + cf) / 2, cont);
			Analizer(matriz, li, (li + lf) / 2, ((ci + cf) / 2) + 1, cf, cont);
			Analizer(matriz, ((li + lf) / 2) + 1, lf, ci, (ci + cf) / 2, cont);
			Analizer(matriz, ((li + lf) / 2) + 1, lf, ((ci + cf) / 2) + 1, cf, cont);
		}
		else if (cf - ci){
			Analizer(matriz, li, (li + lf) / 2, ci, (ci + cf) / 2, cont);
			Analizer(matriz, li, (li + lf) / 2, ((ci + cf) / 2) + 1, cf, cont);
		}
		else{
			Analizer(matriz, li, (li + lf) / 2, ci, (ci + cf) / 2, cont);
			Analizer(matriz, ((li + lf) / 2) + 1, lf, ci, (ci + cf) / 2, cont);
		}
	}
	else if(matriz[li][ci] == 0 || matriz[li][ci] == 1){
		printf("%d", matriz[li][ci]);
		(*cont)++;
	}
}

void Teste(){
	int l, c, cont = 0, i, j;
	int** matriz;

	scanf("%d%d", &l, &c);

	matriz = alocaMatriz(l, c);

	leMatriz(matriz, l, c);

	Analizer(matriz, 0, l - 1, 0, c - 1, &cont);
	printf("\n");

	liberaMatriz(matriz, l, c);
}

int main(){
	int n, i;
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		Teste();
	}
}
//821 - Bitmap
