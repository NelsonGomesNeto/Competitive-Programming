#include <stdio.h>
#define DEBUG if(0)

int swap(int a[], int b[])
{
  int aux[2] = {a[0], a[1]};
  a[0] = b[0]; a[1] = b[1];
  b[0] = aux[0]; b[1] = aux[1];
}

int max(int a, int b)
{
  return(a > b ? a : b);
}

int knapsack(int food[][2], int i, int canGain)
{
  if (i < 0) return(0);
  int ans = knapsack(food, i - 1, canGain);
  if (canGain - food[i][1] >= 0)
    ans = max(ans, knapsack(food, i - 1, canGain - food[i][1]) + food[i][0]);
  return(ans);
}

int main()
{
  int n, canGain; scanf("%d %d", &n, &canGain);
  int food[n][2], i, j; for (i = 0; i < n; i ++) scanf("%d %d", &food[i][0], &food[i][1]);
  for (i = 0; i < n; i ++)
    for (j = i + 1; j < n; j ++)
      if (food[i][1] < food[j][1])
        swap(food[i], food[j]);
  DEBUG for (i = 0; i < n; i ++)
    printf("%d %d\n", food[i][0], food[i][1]);

  int ans = knapsack(food, n - 1, canGain);
  printf("%d\n", ans);
  return(0);
}