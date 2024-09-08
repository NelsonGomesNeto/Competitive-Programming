#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
  int dist(Point &other)
  {
    return abs(x - other.x) + abs(y - other.y);
  }
};

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n, k; scanf("%d %d", &n, &k);
    Point points[n];
    for (int i = 0; i < n; i++)
      points[i].read();

    bool can = false;
    for (int i = 0; i < n; i++)
    {
      bool done = true;
      for (int j = 0; j < n; j++)
        if (points[i].dist(points[j]) > k)
          done = false;
      can |= done;
    }

    printf("%d\n", can ? 1 : -1);
  }
  return 0;
}
