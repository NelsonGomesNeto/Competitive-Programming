#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

set<int> a, b;

int main()
{
  int n, m;
  while (~scanf("%d %d", &n, &m))
  {
    a.clear();
    for (int i = 0; i < n; i++)
    {
      int aa; scanf("%d", &aa);
      a.insert(aa);
    }

    b.clear();
    for (int i = 0; i < m; i++)
    {
      int bb; scanf("%d", &bb);
      b.insert(bb);
    }

    set<int> ans;
    for (int aa: a)
      if (!b.count(aa))
        ans.insert(aa);
    for (int bb: b)
      if (!a.count(bb))
        ans.insert(bb);
    bool first = true;
    for (int i: ans)
    {
      if (!first) printf(" ");
      printf("%d", i);
      first = false;
    }
    printf("\n");
  }
  return 0;
}