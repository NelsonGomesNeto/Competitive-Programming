#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    map<lli, vector<lli> > rock; lli d[n];
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &d[i]);
      if (d[i]) rock[d[i] + i].push_back(i);
    }

    lli best = 0;
    for (int i = n - 1; i >= 0; i --)
      if (rock[i - d[i]].size() > 0)
        best = max(best, (lli) i - rock[i - d[i]][0]);

    printf("%lld\n", best);
  }
  return(0);
}