#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n;
struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
  Point operator-(Point &other) { return Point{x - other.x, y - other.y}; }
  int cross(Point &other)
  {
    return x * other.y - y * other.x;
  }
};
Point points[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      points[i].read();

    bool has = false;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        for (int k = j + 1; k < n; k++)
        {
          Point a = points[i] - points[j];
          Point b = points[i] - points[k];
          if (a.cross(b) == 0)
            has = true;
        }
    printf("%s\n", has ? "Yes" : "No");
  }
  return 0;
}