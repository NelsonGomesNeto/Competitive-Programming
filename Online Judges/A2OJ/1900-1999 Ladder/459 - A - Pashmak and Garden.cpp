#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Point
{
  int x, y;
  int read() { return scanf("%d %d", &x, &y); }
  void print(char ending = '\n') { printf("%d %d%c", x, y, ending); }
};
Point a, b;

int main()
{
  while (~a.read() && ~b.read())
  {
    // a.print();
    // b.print();

    if (a.x == b.x)
    {
      int delta = abs(a.y - b.y);
      Point c = Point{a.x + delta, min(a.y, b.y)};
      Point d = Point{a.x + delta, max(a.y, b.y)};
      c.print(' '); d.print('\n');
    }
    else if (a.y == b.y)
    {
      int delta = abs(a.x - b.x);
      Point c = Point{min(a.x, b.x), a.y + delta};
      Point d = Point{max(a.x, b.x), a.y + delta};
      c.print(' '); d.print('\n');
    }
    else if (abs(a.x - b.x) == abs(a.y - b.y))
    {
      int delta = abs(a.x - b.x);
      if (a.x == b.y || a.y == b.x)
      {
        Point c = Point{a.x, b.y};
        Point d = Point{b.x, a.y};
        c.print(' '); d.print('\n');
      }
      else
      {
        Point c = Point{a.x, b.y};
        Point d = Point{b.x, a.y};
        c.print(' '); d.print('\n');
      }
    }
    else
      printf("-1\n");
  }
  return 0;
}