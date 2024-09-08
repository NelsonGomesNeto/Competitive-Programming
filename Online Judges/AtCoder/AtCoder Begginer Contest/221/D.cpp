#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
map<lli, pair<int, int>> op;
lli ans[maxN + 1];

int main()
{
  while (~scanf("%d", &n))
  {
    op.clear();
    for (int i = 0; i < n; i++)
    {
      lli a, b; scanf("%lld %lld", &a, &b); a--;
      op[a].first++;
      op[a + b].second++;
    }

    memset(ans, 0, sizeof(ans));
    lli prvi = 0, curr = 0;
    for (auto &[i, inout]: op)
    {
      ans[curr] += i - prvi;

      curr += inout.first;
      curr -= inout.second;

      prvi = i;
    }

    for (int i = 1; i <= n; i++)
    {
      printf("%lld%c", ans[i], i < n ? ' ' : '\n');
    }
  }
  return 0;
}