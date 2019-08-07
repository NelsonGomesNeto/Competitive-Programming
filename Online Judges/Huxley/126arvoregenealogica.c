/**
 * Rodrigo Paes
 * 25/10/2011
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NOME 51


typedef struct
{
	char nome[MAX_NOME];
	int indice;
}nome_indice;

int min(int a, int b)
{
	return a<b ? a:b;
}

/**
 * Insere um nome no array de nome_indice. Retorna o ?ndice onde esse elemento foi inserido.
 * Se ele j? tiver sido inserido antes, retorna o ?ndice em que ele foi inserido.
 */
int inserir_nome(char *nome_temp, nome_indice *pessoas, int *tamanho_atual, int maximo)
{

	int i;
	int indice = -1;
	for (i=0 ; i < *tamanho_atual && indice==-1; i++)
	{
		if ( strcmp(nome_temp, pessoas[i].nome) ==0 )
		{
			indice = pessoas[i].indice;
		}
	}
	if (indice==-1)
	{
		pessoas[*tamanho_atual].indice = *tamanho_atual;
		strcpy(pessoas[*tamanho_atual].nome, nome_temp);

		indice = *tamanho_atual;
		(*tamanho_atual)++;
	}

	return indice;
}

/**
 * Retorna o indice do pai, dado um filho.
 * Caso nao tenha pai, o retorno eh -1
 */
int pai(int filho, int **filho_pai, int colunas)
{
	int coluna;
	for (coluna=0 ; coluna < colunas ; coluna ++)
	{
		if (filho_pai[filho][coluna] == 1)
		{
			return coluna;
		}
	}
	return -1; //Se chegar aqui ? porque nao encontrou um pai
}

/**
 * Retorna o grau de parentesco
 */
int grau(int i_pessoa1, int i_pessoa2, int** filho_pai, int tamanho)
{
	if ( i_pessoa1 == i_pessoa2  )
	{
		return 0;
	}
	else if (i_pessoa1==-1 || i_pessoa2==-1)
	{
		/*
		Nesse caso, n?o existe um pai, logo como a fun??o
		grau de parentesco retorna o valor m?nimo, retornamos aqui o maximo,
		para que ele nao influencie na funcao. Ou seja, se existir um caminho
		menor, o menor sera escolhido
		*/
		return INT_MAX;
	}
	else
	{
    int a1 = grau( pai(i_pessoa1,filho_pai,tamanho) , i_pessoa2, filho_pai, tamanho ), a2 = grau( i_pessoa1, pai(i_pessoa2,filho_pai,tamanho), filho_pai, tamanho );
    printf("%d %d\n", a1, a2);
		return 1 + min(a1, a2);
	}
}

/**
  Retorna o nome da pessoa, dado o indice em que ela se encontra na matriz.
  Veja que o indice da matriz nao eh necessariamente o indice do array nome_indice
 */
char * get_nome(int indice_pessoa, nome_indice *pessoas, int tamanho)
{
	int i;
	for (i = 0; i < tamanho; i++)
	{
		if (pessoas[i].indice == indice_pessoa)
		{
			return pessoas[i].nome;
		}
	}
	// Se retornar nulo ? porque o indice esta errado
	return NULL;
}

/**
  Funcao so usada para fins de debug. Imprime a tabela filho_pai
 */
void imprimir_tabela(int **filho_pai, int tamanho)
{
	int i,j;
	for (i=0; i< tamanho; i++)
	{
		for (j=0 ; j< tamanho ;	j++)
		{
			printf("%d ",filho_pai[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int n,i, j, indice_filho, indice_pai, tamanho_atual=0;
	/* Armazenar? a resposta, com os 02 ?ndices das pessoas com maior grau
	   de parentesco
	*/
	int i_pessoa1, i_pessoa2;
	int grau_atual, maior_grau;
	char nome_temp[MAX_NOME], *nome1, *nome2;
	/*
	 Tabela onde as linhas representam os filhos e as colunas os pais.
	 Se o valor for 0, entao nao existe uma relacao filho->pai, se for
	 1, entao existe
	 */
	int **filho_pai;

	scanf("%d",&n);
	getchar();
	/* O numero maximo de pessoas eh 2n */
	nome_indice pessoas[2*n];

	/** Aloca dinamicamente a tabela */
	filho_pai = (int **) malloc(sizeof(int *) *2*n);
	for (i=0 ; i<(2*n) ; i++)
	{
		filho_pai[i] = (int *) malloc (sizeof(int) * 2* n);
		/* inicializa o array com 0*/
		for (j=0; j < (2*n) ; j++)
		{
			filho_pai[i][j] = 0;
		}
	}


	// Leitura dos nomes
	for (i=0; i< n ; i++)
	{

		scanf("%s",nome_temp);
		indice_pai = inserir_nome(nome_temp, pessoas, &tamanho_atual, 2*n);
		scanf("%s",nome_temp);
		indice_filho = inserir_nome(nome_temp, pessoas,&tamanho_atual, 2*n);

		/* Marca uma rela??o de filho-pai */
		filho_pai[indice_filho][indice_pai] = 1;
	}

	//imprimir_tabela(filho_pai,tamanho_atual);

	/** O loop abaixo verifica todos as combinacoes de filho -> pai e guarda as maiores */
	maior_grau = -1;
	for (i=0; i< tamanho_atual ; i++)
	{
		for (j=0; j < tamanho_atual ; j++)
		{
			if (i!=j)
			{
				grau_atual = grau(i,j, filho_pai, tamanho_atual);

				if (grau_atual > maior_grau)
				{
					i_pessoa1 = i;
					i_pessoa2 = j;
					maior_grau = grau_atual;
				}
			}
		}
	}


	/* Ordenar em ordem alfabetica */
	nome1 = get_nome(i_pessoa1, pessoas, tamanho_atual);
	nome2 = get_nome(i_pessoa2, pessoas, tamanho_atual);

	if ( strcmp(nome1,nome2) < 0 )
	{
		printf("%s %s %d\n",nome1,nome2,maior_grau);
	}
	else
	{
		printf("%s %s %d\n",nome2,nome1,maior_grau);
	}


	return 0;
}

