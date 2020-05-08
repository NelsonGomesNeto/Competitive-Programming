#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxA = 200; int n;
int a[maxN], acc[maxA][maxN + 1], cnt[maxA];
vector<int> l[maxA], r[maxA];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
    }

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < maxA; i++)
    {
      l[i].clear(), r[i].clear();
      l[i].push_back(0), r[i].push_back(0);

      for (int j = 0; j < n; j++)
      {
        if (a[j] == i)
          l[i].push_back(j), cnt[i]++;
        acc[i][j + 1] = acc[i][j] + (a[j] == i);
      }

      for (int j = n - 1, c = 0; j >= 0; j--)
        if (a[j] == i)
          r[i].push_back(j);
    }

    int ans = 1;
    for (int i = 0; i < maxA; i++)
    {
      int end = cnt[i] >> 1;
      for (int j = 1; j <= end; j++)
      {
        ans = max(ans, 2*j);
        for (int k = 0; k < maxA; k++)
          ans = max(ans, 2*j + acc[k][r[i][j]] - acc[k][l[i][j] + 1]);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}