#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  char a[n][m + 1], b[n][m + 1];
  for (int i = 0; i < n; i ++) scanf(" %s", a[i]);
  for (int i = 0; i < n; i ++) scanf(" %s", b[i]);

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      if (a[i][j] != b[i][j])
        printf("%d %d\n", i + 1, j + 1);

  return(0);
}