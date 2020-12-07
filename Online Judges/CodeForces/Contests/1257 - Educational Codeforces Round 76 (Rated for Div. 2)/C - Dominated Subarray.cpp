#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5 + 1; int n;
int a[maxN];
vector<int> pos[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i <= n; i ++)
      pos[i].clear();
    int best = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      pos[a[i]].push_back(i);
      best = max(best, (int)pos[a[i]].size());
    }

    if (best <= 1) printf("-1\n");
    else
    {
      int ans = n;
      for (int i = 0; i <= n; i ++)
        if (pos[i].size() >= 2)
          for (int j = 0; j < pos[i].size() - 1; j ++)
            ans = min(ans, pos[i][j + 1] - pos[i][j] + 1);
      printf("%d\n", ans);
    }
  }
  return 0;
}
