#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int MAX = 100001;

int main()
{
  int run = 0, tests; scanf("%d", &tests);
  while (run < tests)
  {
    run ++;
    int size, queries; scanf("%d %d", &size, &queries);
    int set[size], i;
    for (i = 0; i < size; i ++)
      scanf("%d", &set[i]);

    int **subSetSum = malloc((size + 1) * sizeof(int*));// = ma[size + 1][MAX];
    for (i = 0; i <= size; i ++)
    {
      subSetSum[i] = malloc(MAX * sizeof(int));
      memset(subSetSum[i], 0, MAX * sizeof(int));
    }
    for (i = 0; i <= size; i ++)
      subSetSum[i][0] = 1;
    for (i = 1; i < MAX; i ++)
      subSetSum[0][i] = 0;

    int j;
    for (i = 1; i <= size; i ++)
    {
      for (j = 0; j < MAX; j ++)
      {
        if (j < set[i - 1])
          subSetSum[i][j] = subSetSum[i - 1][j];
        else
          subSetSum[i][j] = subSetSum[i - 1][j] || subSetSum[i - 1][j - set[i - 1]];
          // Previous tested set or previous tested set in the position missing
      }
    }

    printf("caso %d:", run);
    int elements, targetSum;
    for (i = 0; i < queries; i ++)
    {
      scanf("%d %d", &elements, &targetSum);
      printf(" %d", subSetSum[elements][targetSum]);
    }
    printf("\n");
  }

  return(0);
}