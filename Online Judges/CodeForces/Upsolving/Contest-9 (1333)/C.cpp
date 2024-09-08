#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];
lli acc[maxN + 1];
map<lli, vector<int>> pos;
int in[maxN], out[maxN];

lli acc2[maxN + 1];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    pos.clear(), memset(in, 0, sizeof(in)), memset(out, 0, sizeof(out));
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + a[i];

    for (int i = 1; i <= n; i++)
      pos[acc[i]].push_back(i);

    lli curr = 0;
    map<int, int> minimuns;
    list<int> removals[n + 1];
    for (int i = 0; i < n; curr += a[i++])
    {
      int p = lower_bound(pos[curr].begin(), pos[curr].end(), i+1) - pos[curr].begin();
      // DEBUG {
      //   printf("\tLOL: ");
      //   for (int j: pos[curr])
      //     printf("%d ", j);
      //   printf("\n");
      //   printf("\t\t%d %lld %d\n", i, curr, p);
      // }

      if (p == pos[curr].size()) continue;
      p = pos[curr][p];
      if (p <= i) continue;

      DEBUG printf("\tin: %d, out: %d || %lld\n", i, p - 1, acc[p] - acc[i]);
      in[i]++, out[p - 1]++;
      if (!minimuns.count(p - 2))
        minimuns[p - 2] = 0;
      minimuns[p - 2]++;
      removals[i + 1].push_back(p - 2);
    }

    lli ans = 0;
    for (int i = 0; i < n; i++)
    {
      for (int r: removals[i])
        if (--minimuns[r] == 0)
          minimuns.erase(r);
      lli end = minimuns.empty() ? n - 1 : minimuns.begin()->first;
      ans += (end - i + 1);
    }

    printf("%lld\n", ans);
  }
  return 0;
}
