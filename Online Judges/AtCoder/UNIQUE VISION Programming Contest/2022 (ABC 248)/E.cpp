#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  bool collinear(Point &b, Point &c)
  {
    return x * (b.y - c.y) + b.x * (c.y - y) + c.x * (y - b.y) == 0;
  }
};

const int maxN = 300; int n, k;
Point points[maxN];

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i < n; ++i)
      points[i].read();

    if (k == 1)
    {
      printf("Infinity\n");
      continue;
    }
    if (k == 2)
    {
      set<set<int>> ans;
      for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
          set<int> now;
          now.insert(i);
          now.insert(j);
          for (int p = 0; p < n; ++p)
            if (p != i && p != j && points[i].collinear(points[j], points[p]))
              now.insert(p);
          ans.insert(now);
        }
      printf("%d\n", (int)ans.size());
      continue;
    }

    set<set<int>> ans;
    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j)
      {
        set<int> now;
        now.insert(i);
        now.insert(j);
        for (int p = 0; p < n; ++p)
          if (p != i && p != j && points[i].collinear(points[j], points[p]))
            now.insert(p);
        if (now.size() >= k)
          ans.insert(now);
      }
    printf("%d\n", (int)ans.size());
  }
  return 0;
}