#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int ans[3];

int main()
{
  memset(ans, 0, sizeof(ans));
  int a[6];
  for (int i = 0; i < 6; i ++) scanf("%d", &a[i]);

  int n; scanf("%d", &n);
  while (n --)
  {
    int got[6]; memset(got, 0, sizeof(got));
    int m; scanf("%d", &m);
    for (int j = 0; j < m; j ++)
    {
      int b; scanf("%d", &b);
      for (int k = 0; k < 6; k ++)
        if (a[k] == b && !got[k])
        {
          got[k] = 1;
          break;
        }
    }
    int s = 0; for (int i = 0; i < 6; i ++) s += got[i];
    if (s >= 4) ans[s - 4] ++;
  }
  printf("%d %d %d", ans[2], ans[1], ans[0]);

  return(0);
}