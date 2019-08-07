#include <stdio.h>
#include <string.h>
#define DEBUG if (0)

void dig(int connection[], int visited[], int start, int curr)
{
  visited[curr] = 1;
  if (start == curr) return;

  dig(connection, visited, start, connection[curr]);
}

void printArray(int a[], int size)
{
  int i;
  for (i = 0; i < size; i ++)
    printf("%d ", a[i]);
  printf("\n");
}

int main()
{
  int holes; scanf("%d", &holes);
  int connection[holes], visited[holes], i;
  memset(visited, 0, sizeof(visited));

  for (i = 0; i < holes; i ++)
    scanf("%d", &connection[i]);

  int tocas = 0;
  for (i = 0; i < holes; i ++)
  {
    if (!visited[i])
    {
      dig(connection, visited, i, connection[i]);
      DEBUG printArray(visited, holes);
      tocas ++;
    }
  }

  printf("%d\n", tocas);

  return(0);
}