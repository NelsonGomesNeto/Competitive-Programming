#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  double mat[n][n]; for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) scanf("%lf", &mat[i][j]);

  double alpha[n]; int fits = 1;
  for (int i = 0; i < n; i ++)
  {
    alpha[i] = 0;
    for (int k = 0; k < i; k ++)
      alpha[i] += alpha[k] * abs(mat[i][k] / mat[i][i]);
    for (int k = i + 1; k < n; k ++)
      alpha[i] += abs(mat[i][k] / mat[i][i]);
    if (alpha[i] >= 1) fits = 0;
  }
  printf("%s\n", fits ? "SIM" : "NAO");
  for (int i = 0; i < n; i ++)
    printf("%.2lf%c", alpha[i], i < n - 1 ? ' ' : '\n');
  return(0);
}