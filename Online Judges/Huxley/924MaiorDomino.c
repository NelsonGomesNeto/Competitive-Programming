#include <stdio.h>

int max(int a, int b)
{
  return(a > b ? a : b);
}

int push(int domino[], int visited[], int curr)
{
  if (visited[curr] == 1) return(curr);

  visited[curr] = 1;
  return(max(curr, push(domino, visited, domino[curr] - 1)));
}

int clean(int a[], int size)
{
  int i;
  for (i = 0; i < size; i ++)
    a[i] = 0;
}

int main()
{
  int size; scanf("%d", &size);
  int domino[size], visited[size], i;
  for (i = 0; i < size; i ++)
    scanf("%d", &domino[i]);

  for (i = 0; i < size; i ++)
  {
    clean(visited, size);
    printf("%d\n", 1 + push(domino, visited, i));
  }

  return(0);
}
