#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e4; int n;
int r[maxN][5];
int lol[maxN];

int cmp(int i, int j)
{
  int cnt = 0;
  for (int k = 0; k < 5; k++)
    cnt += r[i][k] < r[j][k];
  return cnt;
}

int main()
{
  int q; scanf("%d", &q);
  for (int tt = 1; tt <= q; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      lol[i] = i;
      for (int j = 0; j < 5; j++)
        scanf("%d", &r[i][j]);
    }
    sort(lol, lol+n, cmp);

    int end = min(n, 1000);
    int ans = -2;
    for (int i = 0; i < end; i++)
    {
      bool can = true;
      for (int j = 0; j < n; j++)
        if (i != j)
        {
          DEBUG printf("\t%d %d - %d\n", lol[i], lol[j], cmp(lol[i], lol[j]));
          if (cmp(lol[i], lol[j]) < 3)
          {
            can = false;
            break;
          }
        }
      if (can)
        ans = lol[i];
    }
    printf("%d\n", ans + 1);
  }
  return 0;
}