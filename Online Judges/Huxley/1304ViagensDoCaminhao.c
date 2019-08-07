#include <stdio.h>
#define DEBUG if(0)

void printArray(int a[], int size)
{
  int i;
  for (i = 0; i < size; i ++)
    printf("%d ", a[i]);
  printf("\n");
}

int best, nowGot[1001];

void travel(int boxes[], int got[], int i, int qtdBoxes, int value, int capacity)
{
  if (i == qtdBoxes)
  {
    if (value > best)
    {
      int j;
      for (j = 0; j < qtdBoxes; j ++)
        nowGot[j] = got[j];
      best = value;
    }
    return;
  }

  if (capacity - boxes[i] >= 0 && !got[i])
  {
    got[i] = 1;
    travel(boxes, got, i + 1, qtdBoxes, value + boxes[i], capacity - boxes[i]);
    got[i] = 0;
  }
  travel(boxes, got, i + 1, qtdBoxes, value, capacity);
}

int main()
{
  int capacity, travels; scanf("%d %d", &capacity, &travels);
  int boxes[1001], got[1001], i;
  while (scanf("%d", &boxes[i]) != EOF)
  {
    if (boxes[i] > capacity) continue;
    got[i] = 0;
    i ++;
  }
  int qtdBoxes = i;

  i = 0;
  while (i < travels)
  {
    best = 0;
    travel(boxes, got, 0, qtdBoxes, 0, capacity);
    if (best == 0) break;
    int j;
    for (j = 0; j < qtdBoxes; j ++)
      if (nowGot[j]) got[j] = 1;
    DEBUG printArray(got, qtdBoxes);
    printf("VIAGEM %d: %d\n", ++i, best);
  }

  return(0);
}