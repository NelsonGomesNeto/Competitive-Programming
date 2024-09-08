#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
lli w, h; int n;

struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  int border() const
  {
    if (x == 0) return 0;
    if (y == 0) return 1;
    if (x == w) return 2;
    if (y == h) return 3;
    return -1;
  }
  lli borderValue() const
  {
    if (x == 0) return -y;
    if (y == 0) return x;
    if (x == w) return y;
    if (y == h) return -x;
    return -1;
  }
  bool onBorder()
  {
    return border() >= 0;
  }
  bool operator<(const Point &other) const
  {
    return border() < other.border() ||
          (border() == other.border() && borderValue() < other.borderValue());
  }
};
struct Segment
{
  Point a, b;
  void read() { a.read(); b.read(); }
  bool onBorder()
  {
    return a.onBorder() && b.onBorder();
  }
};
Segment segments[maxN];
vector<pair<Point, int>> borderSegments;

int main()
{
  while (~scanf("%lld %lld", &w, &h))
  {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
      segments[i].read();

    borderSegments.clear();
    for (int i = 0; i < n; ++i)
      if (segments[i].onBorder())
      {
        borderSegments.emplace_back(segments[i].a, i);
        borderSegments.emplace_back(segments[i].b, i);
      }
    sort(borderSegments.begin(), borderSegments.end());

    bool can = true;
    stack<int> s;
    for (const auto& [p, i]: borderSegments)
    {
      DEBUG printf("\t(%lld, %lld) - %d\n", p.x, p.y, i);
      if (!s.empty() && s.top() == i) s.pop();
      else s.push(i);
    }
    can &= s.empty();
    printf("%s\n", can ? "Y" : "N");
  }
  return 0;
}