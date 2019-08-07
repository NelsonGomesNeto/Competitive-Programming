#include <stdio.h>

int best = 0;

void printArray(int a[], int size)
{
  int i;
  for (i = 0; i < size; i ++)
    printf("%d ", a[i]);
  printf("\n");
}

void backtracking(int putted[], int value[], int weight[], int i, int itens, int actualValue, int actualCapacity)
{
  if (i == itens)
  {
    printArray(putted, itens);
    if (actualValue > best)
      best = actualValue;
    return;
  }

  putted[i] = -1;
  backtracking(putted, value, weight, i + 1, itens, actualValue, actualCapacity);
  if (actualCapacity - weight[i] >= 0)
  {
    putted[i] = value[i];
    backtracking(putted, value, weight, i + 1, itens, actualValue + value[i], actualCapacity - weight[i]);
  }
}

int main()
{
  int itens, capacity; scanf("%d %d", &itens, &capacity);
  int value[itens], weight[itens], i;
  for (i = 0; i < itens; i ++)
    scanf("%d", &value[i]);
  for (i = 0; i < itens; i ++)
    scanf("%d", &weight[i]);

  int putted[itens];
  backtracking(putted, value, weight, 0, itens, 0, capacity);

  printf("%d\n", best);

  return(0);
}