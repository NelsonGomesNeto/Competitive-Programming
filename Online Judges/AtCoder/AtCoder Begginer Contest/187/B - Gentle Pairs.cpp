#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
};
Point points[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      points[i].read();

    int ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
      {
        Point u = {points[j].x - points[i].x, points[j].y - points[i].y};
        ans += abs(u.x) >= abs(u.y);
      }
    printf("%d\n", ans);
  }
  return 0;
}