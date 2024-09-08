#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e2; int n, m;
char s[maxN][maxN + 1];
int acc[maxN][maxN + 1];

int spruce[maxN];
bool isSpruce(int i, int j, int k)
{
  int base = 2*k + 1;
  if (j + base - 1 >= m) return false;
  if (i - k < 0) return false;

  for (int h = 0; h <= k; h++)
  {
    int sum = acc[i - h][j + base] - acc[i - h][j];
    DEBUG printf("\t%d %d %d - %d %d | %d\n", i, j, k, h, base, sum);
    if (sum != base) return false;
    base -= 2;
    j++;
  }
  return true;
}

int main()
{
  for (int k = 0; k < maxN; k++)
  {
    int base = 2*k + 1;
    for (int h = 0; h <= k; h++)
    {
      spruce[k] += base;
      base -= 2;
    }
  }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
      scanf(" %s", s[i]);

    for (int i = 0; i < n; i++)
    {
      acc[i][0] = 0;
      for (int j = 0; j < m; j++)
        acc[i][j + 1] = acc[i][j] + (s[i][j] == '*');
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
      {
        int lo = 0, hi = n - 1;
        while (lo < hi)
        {
          int mid = (lo + hi + 1) >> 1;
          if (isSpruce(i, j, mid)) lo = mid;
          else hi = mid - 1;
        }
        if (isSpruce(i, j, lo))
        {
          DEBUG printf("%d %d - %d | %d\n", i, j, lo, isSpruce(i, j, lo));
          ans += lo + 1;
          // for (int k = 0; k <= lo; k++)
          //   ans += spruce[k];
        }

        // for (int k = 0; k < n; k++)
        // {
        //   bool is = isSpruce(i, j, k);
        //   DEBUG printf("\t[%d, %d, %d] = %d\n", i, j, k, is);
        //   ans += is;
        //   if (!is) break;
        // }
      }
    printf("%d\n", ans);
  }
  return 0;
}
