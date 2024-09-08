#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxH = 1e5, maxF = 1e5; int n; lli targetFruits;
struct Tree
{
  int height, fruits;
};
Tree trees[maxN];

bool can(int minH, int minF)
{
  lli totalFruits = 0;
  for (int i = 0; i < n; i++)
    if (trees[i].height >= minH && trees[i].fruits >= minF)
      totalFruits += trees[i].fruits;
  return totalFruits >= targetFruits;
}
int findFruitCutOffPoint(int minH)
{
  int lo = 0, hi = maxF;
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (can(minH, mid)) lo = mid;
    else hi = mid - 1;
  }
  return can(minH, lo) ? lo : -1;
}
pair<int, int> solve()
{
  int lo = 0, hi = maxH;
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (findFruitCutOffPoint(mid) != -1) lo = mid;
    else hi = mid - 1;
  }
  return make_pair(lo, findFruitCutOffPoint(lo));
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %lld", &n, &targetFruits);
      for (int i = 0; i < n; i++)
        scanf("%d", &trees[i].height);
      for (int i = 0; i < n; i++)
        scanf("%d", &trees[i].fruits);

      pair<int, int> ans = solve();
      if (ans.second == -1) printf("Impossible\n");
      else printf("%d %d\n", ans.first, ans.second);
    }
  return 0;
}