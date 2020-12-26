#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 20; int n;
int mat[3][maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < 3; i ++)
    for (int j = 0; j < n - (i == 2); j ++)
      scanf("%d", &mat[i][j]);


  int ans = 0;
  for (int i = 0; i < n; i ++)
    ans += mat[1][mat[0][i] - 1];

  for (int i = 0; i < n - 1; i ++)
    if (mat[0][i + 1] == mat[0][i] + 1)
      ans += mat[2][mat[0][i] - 1];

  printf("%d\n", ans);

  return(0);
}