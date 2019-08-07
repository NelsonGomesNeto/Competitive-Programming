#include <stdio.h>
#define DEBUG if(0)
int inf = 10000000;

int findSmallest(int array[], int size)
{
  int i, smallest = inf, si = 0;
  for (i = 0; i < size; i ++)
  {
    if (array[i] == -inf) continue;
    if (array[i] < smallest)
    {
      smallest = array[i];
      si = i;
    }
  }
  return(si);
}

int abso(int a)
{
  return(a < 0 ? -a : a);
}

int findPos(int array[], int size, int nowSmall, int query)
{
  int i, j;
  for (i = nowSmall, j = 0;;)
  {
    if (i < 0) i = size - 1;
    i %= size;
    if (array[i] != -inf)
      j ++;
    if (j == 1 + abso(query)) break;

    if (query < 0) i --;
    else i ++;
  }
  return(i);
}

void printArray(int array[], int size, int toDo)
{
  int i, now;
  for (i = findSmallest(array, size) % size, now = 0; now < toDo; i ++)
  {
    i %= size;
    if (array[i] != -inf)
    {
      printf("%d", array[i]);
      if (now < toDo - 1) printf(" ");
      else printf("\n");
      now ++;
    }
  }
}

int main()
{
  int size, queries; scanf("%d %d", &size, &queries);
  int array[size], i;
  for (i = 0; i < size; i ++)
    scanf("%d", &array[i]);

  printArray(array, size, size);

  int query, j, k, new, nowSmall, queryStart;
  for (i = 0; i < queries; i ++)
  {
    scanf("%d", &query);
    new = 0; nowSmall = findSmallest(array, size);
    queryStart = findPos(array, size, nowSmall, query) % size;
    DEBUG printf("queryStart: %d\n", queryStart);
    for (j = queryStart, k = 0; k < 2; j ++)
    {
      j %= size;
      DEBUG printf("now: %d %d\n", j, array[j]);
      if (array[j] == -inf) continue;
      new += array[j];
      array[j] = -inf;
      k ++;
    }
    array[queryStart] = new;
    printArray(array, size, size - i - 1);
  }

  return(0);
}