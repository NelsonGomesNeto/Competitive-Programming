#include <stdio.h>

int total = 0;

void backtracking(int i, int dices, int sum, int distance)
{
  if (i == dices)
  {
    if (sum >= distance)
      total ++;
    return;
  }

  int k;
  for (k = 1; k <= 6; k ++)
    backtracking(i + 1, dices, sum + k, distance);
}

int main()
{
  int dices, distance; scanf("%d %d", &dices, &distance);

  backtracking(0, dices, 0, distance);

  printf("%d\n", total);
  
  return(0);
}