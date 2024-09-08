#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 500; int n;
struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
};
Point ps[maxN];
set<pair<int, int>> ans;

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      ps[i].read();

    ans.clear();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (i != j)
        {
          int dx = ps[i].x - ps[j].x;
          int dy = ps[i].y - ps[j].y;
          int g = gcd(abs(dx), abs(dy));
          if (g == 0) g = 1;
          ans.insert(make_pair(dx / g, dy / g));
        }

    printf("%d\n", (int)ans.size());
  }
  return 0;
}