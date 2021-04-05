#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  type 1:
    k += x * a
  type 2:
    k *= x ^ a
*/

const lli DIV = 1e5;
lli safeCeil(lli x, lli y)
{
  return (x + y - 1) / y;
}

const int maxN = 300, maxM = 1e5; int n, m;
struct Op
{
  int t; lli x; int y;
  void read()
  {
    scanf("%d %lld %d", &t, &x, &y);
  }
};
Op ops[maxN];
int ans[maxM + 1];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++)
      ops[i].read();

    set<int> missing;
    for (int i = 1; i <= m; i++)
    {
      ans[i] = 1e6;
      missing.insert(i);
    }

    set<int> starts;
    starts.insert(0);

    for (int i = 0; i < n && missing.size(); i++)
    {
      set<int> newStarts;

      for (int k0: starts)
      {
        lli curr = k0;
        for (int a = 0; a < ops[i].y; a++)
        {
          if (ops[i].t == 1)
            curr = curr + safeCeil(ops[i].x, DIV);
          else
            curr = safeCeil(curr * ops[i].x, DIV);

          if (curr > *missing.rbegin())
            break;

          ans[curr] = min(ans[curr], i + 1);
          if (!starts.count(curr))
            newStarts.insert(curr);
          else
            break;
        }
      }

      for (int k0: newStarts)
      {
        starts.insert(k0);
        auto it = missing.find(k0);
        if (it != missing.end())
          missing.erase(it);
      }
    }

    for (int i = 1; i <= m; i++)
    {
      if (ans[i] >= 1e6)
        ans[i] = -1;
      printf("%d%c", ans[i], i < m ? ' ' : '\n');
    }
  }
  return 0;
}