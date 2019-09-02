#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int mat[n][n];
  for (int i = 0, a = 0; i < n; i += 4)
    for (int j = 0; j < n; j += 4)
      for (int ii = i; ii < i + 4; ii ++)
        for (int jj = j; jj < j + 4; jj ++, a ++)
          mat[ii][jj] = a;
  for (int i = 0; i < n; i ++)
  {
    for (int j = 0; j < n; j ++)
      printf("%d ", mat[i][j]);
    printf("\n");
  }

  return(0);
}
