#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define work struct work

int works, final, best;

work
{
  int pontos, inicio, fim;
};

int compare(const void *c, const void *d)
{
  const work *a = c, *b = d;
  if (a->inicio < b->inicio || (a->inicio == b->inicio && a->fim < b->fim))
    return(-1);
  return(1);
}

void merge(work v[], int start, int mid, int end)
{
  int sizeA = mid - start + 1;
  int sizeB = end - mid;
  int i, j;
  work *A = malloc((sizeA + 1) * sizeof(work));
  work *B = malloc((sizeB + 1) * sizeof(work));

  for (i = start, j = 0; j < sizeA; i ++, j ++)
  {
    A[j] = v[i];
  } A[j].inicio = 9999999; A[j].fim = 9999999;
  for (i = mid + 1, j = 0; j < sizeB; i ++, j ++)
  {
    B[j] = v[i];
  } B[j].inicio = 9999999; B[j].fim = 9999999;

  int k; i = 0; j = 0;
  for (k = start; k <= end; k ++)
  {
    if (A[i].inicio < B[j].inicio || (A[i].inicio == B[j].inicio && A[i].fim < B[j].fim))
    {
      v[k] = A[i]; i ++;
    }
    else
    {
      v[k] = B[j]; j ++;
    }
  }
  free(A); free(B);
}

void mergeSort(work t[], int start, int end)
{
  if (start < end)
  {
    int mid = (end + start) / 2;
    mergeSort(t, start, mid);
    mergeSort(t, mid + 1, end);
    merge(t, start, mid, end);
  }
}

int max(int a, int b)
{
  return(a > b ? a : b);
}

int dp(int pd[], work t[], int i, int minutos)
{
  if (i == final)
  {
    return(0);
  }
  if (pd[minutos] == -1)
  {
    pd[minutos] = dp(pd, t, i + 1, minutos);
    if (t[i].inicio >= minutos)
    {
      pd[minutos] = max(pd[minutos], dp(pd, t, i + 1, t[i].fim) + t[i].pontos);
    }
  }
  return(pd[minutos]);
}

int at(char dia[])
{
  if (strcmp(dia, "Seg") == 0)
    return(0);
  if (strcmp(dia, "Ter") == 0)
    return(1);
  if (strcmp(dia, "Qua") == 0)
    return(2);
  if (strcmp(dia, "Qui") == 0)
    return(3);
  if (strcmp(dia, "Sex") == 0)
    return(4);
}

char* on(int dia)
{
  if (dia == 0)
    return("Seg");
  if (dia == 1)
    return("Ter");
  if (dia == 2)
    return("Qua");
  if (dia == 3)
    return("Qui");
  if (dia == 4)
    return("Sex");
}

int main()
{
  int i;
  while (scanf("%d", &works) && works != 0)
  {
    int codLixo, pontos; char dia[4]; int hI, mI, hF, mF;
    work w[5][works + 1]; int *quanti = calloc(5, sizeof(int));
    int DP[24 * 60];
    for (i = 0; i < works; i ++)
    {
      scanf("%d %d %s %d:%d %d:%d", &codLixo, &pontos, dia, &hI, &mI, &hF, &mF);
      w[at(dia)][quanti[at(dia)]].pontos = pontos;
      w[at(dia)][quanti[at(dia)]].inicio = (hI * 60) + mI;
      w[at(dia)][quanti[at(dia)]].fim = (hF * 60) + mF;
      quanti[at(dia)] ++;
      //printf("%d: %d %d %d\n", quanti[at(dia)], w[at(dia)][quanti[at(dia)]].pontos, w[at(dia)][quanti[at(dia)]].inicio, w[at(dia)][quanti[at(dia)]].fim);
    }

    int ans[5], total = 0;
    for (i = 0; i < 5; i ++)
    {
      memset(DP, -1, 24 * 60 * sizeof(int));
      best = 0; final = quanti[i];
      if (quanti[i] > 0)
      {
        int o, b;
        /*for (o = 0; o < quanti[i]; o ++)
        {
          for (b = o + 1; b < quanti[i]; b ++)
          {
            if (w[i][b].inicio < w[i][o].inicio)
            {
              w[i][works] = w[i][b];
              w[i][b] = w[i][o];
              w[i][o] = w[i][works];
            }
            else if (w[i][b].inicio == w[i][o].inicio)
            {
              if (w[i][b].fim < w[i][o].fim)
              {
                w[i][works] = w[i][b];
                w[i][b] = w[i][o];
                w[i][o] = w[i][works];
              }
            }
          }
        }*/
        mergeSort(w[i], 0, quanti[i] - 1);
        //qsort(w[i], quanti[i], sizeof(work), compare);
        best = dp(DP, w[i], 0, 0);
      }
      ans[i] = best; total += best;
    }

    printf("Total de pontos: %d\n", total);
    for (i = 0; i < 5; i ++)
    {
      printf("%s: %d\n", on(i), ans[i]);
    }

    free(quanti);
  }
  return(0);
}
