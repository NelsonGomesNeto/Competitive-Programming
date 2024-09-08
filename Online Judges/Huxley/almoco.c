#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int atual, inversoes;

void insert(int ar[], int pos, int num)
{
  printf("~~%d\n", pos);
  inversoes += pos;
  if (ar[pos] == 0)
  {
    ar[pos] = num;
  }
  else if (ar[pos] > num)
  {
    memmove(ar + pos + 1, ar + pos, sizeof(int) * (atual + 1));
    ar[pos] = num;
  }
  else if (ar[pos] <= num)
  {
    pos ++;
    memmove(ar + pos + 1, ar + pos, sizeof(int) * (atual + 1));
    ar[pos --] = num;
  }
}

void binS(int a[], int start, int end, int target)
{
  //printf("##%d %d\n", end, start);
  int mid = (end + start) / 2;
  if (end < start)
  {
    insert(a, mid, target);
    return;
  }
  if (target < a[mid])
  {
    return(binS(a, start, mid - 1, target));
  }
  if (target > a[mid])
  {
    return(binS(a, mid + 1, end, target));
  }
  insert(a, mid, target);
  return;
}

int main()
{
  long long int velha, nova;
  scanf("%lld %lld", &velha, &nova);
  long long int buy, i, j, pos;
  int *ocupado = calloc(nova, sizeof(int));
  int *old = calloc(velha, sizeof(int));
  inversoes = 0;
  for (i = 0; i < velha; i ++)
  {
    scanf("%lld", &buy);
    atual = i;
    binS(old, 0, i, buy);
    ocupado[i] = 1;
    for (j = 0; j < i + 1; j ++)
    {
      printf("%d ", old[j]);
    } printf("\n");
  }
  for (i = 0; i < velha; i ++)
  {
    pos = buy % nova; j = 1;
    while (ocupado[pos] == 1)
    {
      pos = (buy + (j * inversoes)) % nova; j ++;
    }
    printf("%lld\n", pos);
    ocupado[pos] = 1;
    ocupado[i] = 0;
  }
  return(0);
}
