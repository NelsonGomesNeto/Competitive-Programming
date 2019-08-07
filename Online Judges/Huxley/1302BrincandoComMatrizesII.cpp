#include <bits/stdc++.h>
using namespace std;

int main()
{
  int mat[3][3], smallest = 1<<20, sum = 0;
  double average = 0, positive = 0;
  for (int i = 0; i < 3; i ++)
    for (int j = 0; j < 3; j ++)
    {
      scanf("%d", &mat[i][j]);
      if (mat[i][j] > 0)
      {
        positive ++;
        average += mat[i][j];
      }
      if (i != j) sum += mat[i][j];
      smallest = min(smallest, mat[i][j]);
    }

  average /= positive;
  printf("%.2lf %d %d %d\n", average, smallest, !(smallest & 1), sum);

  return(0);
}