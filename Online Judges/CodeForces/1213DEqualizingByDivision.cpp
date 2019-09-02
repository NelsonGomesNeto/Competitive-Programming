#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n, k;
int a[maxN];
vector<int> cost[maxN + 1];

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i <= maxN; i ++) cost[i].clear();

    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      int c = 0, x = a[i];
      cost[a[i]].push_back(0);
      while (x)
      {
        x >>= 1, c ++;
        cost[x].push_back(c);
      }
    }

    int ans = 1e9;
    for (int i = 0; i <= maxN; i ++)
      if (cost[i].size() >= k)
      {
        sort(cost[i].begin(), cost[i].end());
        ans = min(ans, accumulate(cost[i].begin(), cost[i].begin() + k, 0));
      }
    printf("%d\n", ans);
  }
  return(0);
}