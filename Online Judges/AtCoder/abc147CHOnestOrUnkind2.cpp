#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 15; int n;
bool honest[maxN];
vector<pair<int, int>> testemonies[maxN];

bool valid(int bitmask)
{
  for (int i = 0; i < n; i ++)
    if (bitmask & (1 << i))
      for (auto &v: testemonies[i])
        if (v.second != ((bitmask >> v.first) & 1))
          return false;
  return true;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++) honest[i] = true, testemonies[i].clear();
    for (int i = 0; i < n; i ++)
    {
      int a; scanf("%d", &a);
      for (int j = 0; j < a; j ++)
      {
        int u, is; scanf("%d %d", &u, &is); u --;
        testemonies[i].push_back({u, is});
      }
    }

    int ans = 0;
    for (int bitmask = 0, end = 1 << n; bitmask < end; bitmask ++)
      if (valid(bitmask))
        ans = max(ans, __builtin_popcount(bitmask));
    printf("%d\n", ans);
  }
  return 0;
}