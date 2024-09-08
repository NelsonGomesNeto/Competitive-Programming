#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define work struct work

int works;

work
{
  int inicio, fim, lucro;
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

int dp(int pd[], work t[], int i, int tempo)
{
  if (i == works)
  {
    return(0);
  }
  if (pd[tempo] == -1)
  {
    pd[tempo] = dp(pd, t, i + 1, tempo);
    if (t[i].inicio > tempo)
    {
      pd[tempo] = max(pd[tempo], dp(pd, t, i + 1, t[i].fim) + t[i].lucro);
    }
  }
  return(pd[tempo]);
}

int main()
{
  int caso = 1;
  while (scanf("%d", &works) != EOF)
  {
    if (caso > 1) printf("\n");
    int i; work w[works + 1];
    int *DP = malloc(3651 * sizeof(int));
    memset(DP, -1, 3651 * sizeof(int));
    for (i = 0; i < works; i ++)
    {
      scanf("%d %d %d", &w[i].inicio, &w[i].fim, &w[i].lucro);
    }
    int o, b;
    /*for (o = 0; o < works; o ++)
    {
      for (b = o + 1; b < works; b ++)
      {
        if (w[b].inicio < w[o].inicio || (w[b].inicio == w[o].inicio && w[b].fim < w[o].fim))
        {
          w[works] = w[b];
          w[b] = w[o];
          w[o] = w[works];
        }
      }
    }
    */
    mergeSort(w, 0, works - 1);
    //qsort(w, works, sizeof(work), compare);
    int ans = dp(DP, w, 0, 0);
    printf("caso %d: %d\n", caso, ans);
    caso ++;
  }
  return(0);
}
