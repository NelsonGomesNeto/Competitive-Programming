#include <stdio.h>
#define MAX_NOME 500
#define MASCULINO 0
#define MAX_CLIENTES 1000
struct cliente
{
	int codigo;
	char nome[MAX_NOME+1];
	int dia_nascimento;
	int mes_nascimento;
	int ano_nascimento;
	int sexo;
  char CPF[100];
};

void imprimir(struct cliente c)
{
	printf("Codigo.......: %d\n", c.codigo);
	printf("Nome.........: %s", c.nome);
	printf("Nascimento...: %d/%d/%d\n", c.dia_nascimento, c.mes_nascimento, c.ano_nascimento);
	printf("Sexo.........: ");
	if (c.sexo==MASCULINO)
	{
		printf("masculino\n");
	}
	else
	{
		printf("feminino\n");
	}
  printf("CPF..........: %s\n", c.CPF);
}

float media_idades(struct cliente c[], int tam)
{
  int i; float idade = 0, media;
  for (i = 0; i < tam; i ++)
  {
    idade += 2016 - c[i].ano_nascimento;
  }
  media = idade / tam;
  printf("Média idades.: %.2f\n", media);
  return(media);
}

int main()
{
	int n, i;
	struct cliente c[MAX_CLIENTES];
	scanf("%d",&n);
	for (i=0; i<n; ++i)
	{
		c[i].codigo = i;
		getchar();
		fgets(c[i].nome , MAX_NOME, stdin);
		scanf("%d%d%d", &c[i].dia_nascimento, &c[i].mes_nascimento, &c[i].ano_nascimento);
		scanf("%d", &c[i].sexo);
    getchar();
    scanf("%s", c[i].CPF);
	}

	for (i=0; i<n; ++i)
	{
		imprimir(c[i]);
	}
  media_idades(c, n);
	return 0;
}
