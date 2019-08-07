#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e3, maxP = 1e3, inf = 1e5; int n, p, highest;
int minMovements[maxN];
vector<int> stacks[maxP];

int getMinMovement(int i, int j, bool side)
{
  int ans = stacks[i].size() - j - 1;
  if (i > 0 && i < p - 1)
  {
    if (side == 0) ans += stacks[i - 1].size() > j ? minMovements[stacks[i - 1][j]] : 0;
    if (side == 1) ans += stacks[i + 1].size() > j ? minMovements[stacks[i + 1][j]] : 0;
  }
  return(ans);
}

int main()
{
  while (scanf("%d %d", &n, &p) && (n || p))
  {
    highest = 0; for (int i = 0; i < p; i ++) stacks[i].clear();
    for (int i = 0, a, b; i < p; i ++)
    {
      scanf("%d", &a); highest = max(highest, a);
      for (int j = 0; j < a; j ++)
      {
        scanf("%d", &b);
        stacks[i].push_back(b - 1);
      }
    }

    for (int i = 0; i < n; i ++) minMovements[i] = inf;
    for (int j = highest - 1; j >= 0; j --)
      for (int lo = 0, hi = p - 1; lo < p; lo ++, hi --)
      {
        if (lo >= 0 && lo < p && stacks[lo].size() > j) minMovements[stacks[lo][j]] = min(minMovements[stacks[lo][j]], 1 + getMinMovement(lo, j, 0));
        if (hi >= 0 && hi < p && stacks[hi].size() > j) minMovements[stacks[hi][j]] = min(minMovements[stacks[hi][j]], 1 + getMinMovement(hi, j, 1));
      }
    printf("%d\n", minMovements[0] - 1);
  }
  return(0);
}