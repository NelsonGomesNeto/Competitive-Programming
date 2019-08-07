#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
const int maxN = 1000; int n, m;
// [0, 1] -> 0, [1, 2] -> 1
int mids[maxN], a[maxN];
struct Fact
{
  int t, lo, hi;
  bool operator<(const Fact &f) const
  {
    return(lo < f.lo || (lo == f.lo && hi < f.hi));
  }
};
Fact facts[maxN];
 
int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++) a[i] = 1;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %d", &facts[i].t, &facts[i].lo, &facts[i].hi);
    facts[i].lo --, facts[i].hi --;
  }
  sort(facts, facts+m);
  reverse(facts, facts+m);
 
  bool can = true;
 
  for (int i = 0; i < m; i ++)
    if (facts[i].t == 1)
      for (int j = facts[i].lo; j < facts[i].hi; j ++)
        mids[j] = 1;
 
  for (int i = 0; i < m; i ++)
    if (facts[i].t == 0)
    {
      bool allInvalid = true;
      for (int j = facts[i].lo; j < facts[i].hi; j ++)
        if (!mids[j])
        {
          allInvalid = false;
          a[j] = a[j + 1] + 1;
          break;
        }
      if (allInvalid) can = false;
    }
  if (!can) printf("NO\n");
  else
  {
    printf("YES\n");
    for (int i = 0; i < n; i ++) printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
  }
 
  return(0);
}