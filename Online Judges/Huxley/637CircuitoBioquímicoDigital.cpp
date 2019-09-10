#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3; int p, n, c;
int mat[maxN + 1][maxN], cnt[maxN + 1];

int main()
{
  while (scanf("%d %d %d", &p, &n, &c) != EOF && p + n + c)
  {
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < p; j ++)
        scanf("%d", &mat[i][j]);
    for (int j = 0; j < p; j ++) mat[n][j] = 0;

    memset(cnt, 0, sizeof(cnt));
    for (int j = 0; j < p; j ++)
      for (int i = 0; i < n; i ++)
        if (mat[i][j] == 1)
        {
          int k = i;
          while (mat[k][j] == 1) k ++;
          cnt[k - i] ++;
          i = k - 1;
        }
    int ans = 0;
    for (int i = c; i <= p; i ++)
      ans += cnt[i];
    printf("%d\n", ans);
  }
  return(0);
}