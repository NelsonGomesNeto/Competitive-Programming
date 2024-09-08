#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  Vertical Segments: two consecutive points sharing the same x

  For each polygon, we need to find which vertical segments are opening and closing:
    For each segment (sorted by x):
      if query segtree [segment.y0 : segment.y1] is set:
        closing
      else:
        opening
      update segtree

  For each segment (of all polygons and points and sorted by x)
    if segment:
      update set accordingly to segment mode
    if point:
      query position to know how many open polygons are there
*/

const int maxN = 1e5; int n, m;
struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
  bool operator<(const Point &other) const { return x < other.x; }
};
struct Segment
{
  // a.x should be equal to b.x, always!!
  Point a, b; bool opening;
  bool operator<(const Segment &other) const { return a.x < b.x; }
};

vector<Point> polygons[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      int m; scanf("%d", &m);
      polygons[i].resize(m);
      for (int j = 0; j < m; j++)
        polygons[i][j].read();
      sort(polygons[i].begin(), polygons[i].end());
    }


  }
  return 0;
}