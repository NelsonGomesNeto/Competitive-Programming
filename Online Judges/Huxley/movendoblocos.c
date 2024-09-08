#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tam;
//struct de posição dos blocos na matriz
struct blocks
{
  int y, x;
};

void printaTudo(int m[][tam])
{
  int i, j;
  for (i = 0; i < tam; i ++)
  {
    printf("%d:", i);
    for (j = 0; j < tam; j ++)
    {
      if (m[i][j] != -1)
        printf(" %d", m[i][j]);
    } printf("\n");
  }
}
//Envia o bloco para seu local original
void sendBack(int ma[][tam], struct blocks p[], int y, int x)
{
  int i, j, bloco = ma[y][x];
  for (i = bloco, j = tam - 1; j >= 0; j --)
  {
    if (ma[i][j] != -1)
    {
      ma[i][j + 1] = bloco;
      p[bloco].y = i;
      p[bloco].x = j + 1;
      return;
    }
  }
  ma[i][0] = bloco;
  p[bloco].y = i;
  p[bloco].x = 0;
}
//Retorna os blocos empilhados em 'x' para sua posição original
void retornaBlocos(int mt[][tam], struct blocks ps[], int bloco)
{
  int i, j;
  for (i = ps[bloco].y, j = tam - 1; j > ps[bloco].x; j --)
  {
    if (mt[i][j] != -1)
    {
      sendBack(mt, ps, i, j);
      mt[i][j] = -1;
    }
  }
}
//retorna a posição de fim da pilha
int finalPilha(int ma[][tam], struct blocks p[], int de)
{
  int i, j;
  for (i = p[de].y, j = p[de].x; j < tam; j ++)
  {
    if (ma[i][j] == -1)
    {
      return(j);
    }
  }
}
//Põe um bloco sobre o outro
void empilha(int ma[][tam], struct blocks p[], int de, int para)
{
  int i, j;
  for (i = p[para].y, j = tam - 1; j >= p[para].x; j --)
  {
    if (ma[i][j] != -1)
    {
      ma[i][j + 1] = de;
      p[de].y = p[para].y;
      p[de].x = j + 1;
      return;
    }
  }
}
//Executa o comando mover 'a' sobre 'b'
void moverSobre(int m[][tam], struct blocks pos[], int from, int to)
{
  retornaBlocos(m, pos, from);
  m[ pos[from].y ][ pos[from].x ] = -1;

  retornaBlocos(m, pos, to);
  m[ pos[to].y ][ pos[to].x + 1 ] = from;

  pos[from].y = pos[to].y;
  pos[from].x = pos[to].x + 1;
}
//Executa o comando mover 'a' acima 'b'
void moverAcima(int m[][tam], struct blocks pos[], int from, int to)
{
  retornaBlocos(m, pos, from);
  m[ pos[from].y ][ pos[from].x ] = -1;

  empilha(m, pos, from, to);
}
//Executa o comando pilha 'a' sobre 'b'
void pilhaSobre(int m[][tam], struct blocks pos[], int from, int to)
{
  retornaBlocos(m, pos, to);

  int i = pos[from].y, j = pos[from].x;
  for (; j < tam; j ++)
  {
    if (m[i][j] != -1)
    {
      empilha(m, pos, m[i][j], to);
      m[i][j] = -1;
    }
  }
}
//Executa o comando pilha 'a' acima 'b'
void pilhaAcima(int m[][tam], struct blocks pos[], int from, int to)
{
  int i, j, fim = finalPilha(m, pos, from);
  for (i = pos[from].y, j = pos[from].x; j < fim; j ++)
  {
    if (m[i][j] != -1)
    {
      empilha(m, pos, m[i][j], to);
      m[i][j] = -1;
    }
  }
}

int main()
{
  scanf("%d", &tam); getchar();//Lê o número de blocos
  int pilha[tam][tam], i, j;
  struct blocks b[tam];
  for (i = 0; i < tam; i ++) //Prepara a """"pilha"""" feita com matriz e struct
  {
    pilha[i][0] = i;
    b[i].y = i; b[i].x = 0;
    for (j = 1; j < tam; j ++)
    {
      pilha[i][j] = -1;
    }
  }
  char comando[10], opera[10]; int from, to; //Lê o começo do comando
  while (scanf("%s", comando) && strcmp(comando, "final") != 0)
  {
    scanf("%d", &from); getchar(); //Lê o bloco 'a'
    scanf("%s", opera); //Lê o final do comando
    scanf("%d", &to); getchar(); //Lê o bloco 'b'
    if (from >= tam || to >= tam || from == to || b[from].y == b[to].y)
    { //IMPORTANTE
      continue; //Verifica se o comando é inválido
    } //IMPORTANTE
    if (strcmp(comando, "mover") == 0) //Só vai
    {
      if (strcmp(opera, "sobre") == 0)
      {
        moverSobre(pilha, b, from, to);
      }
      else //acima
      {
        moverAcima(pilha, b, from, to);
      }
    }
    else //pilha
    {
      if (strcmp(opera, "sobre") == 0)
      {
        pilhaSobre(pilha, b, from, to);
      }
      else //acima
      {
        pilhaAcima(pilha, b, from, to);
      }
    }
  }
  printaTudo(pilha);
  return(0);
}
