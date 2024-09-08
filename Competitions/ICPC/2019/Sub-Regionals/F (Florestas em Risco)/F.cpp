#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4, maxX = 1e5; int n, p;
struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
};
struct Segment
{
  Point down, up; bool left;
  bool operator<(const Segment &other) const { return down.x < other.down.x; }
  void read()
  {
    down.read(); up.read();
    if (down.x > up.x) swap(down, up);
    else if (down.y > up.y) swap(down, up);
  }
  void print() { printf("(%lld, %lld) - (%lld, %lld) [%d]\n", down.x, down.y, up.x, up.y, left); }
  pair<Segment, Segment> getWalls(Segment &rectangle, int r)
  {
    if (down.y == up.y)
      return make_pair(Segment{{max(down.x - r, rectangle.down.x), max(down.y - r, rectangle.down.y)},
                               {max(down.x - r, rectangle.down.x), min(down.y + r, rectangle.up.y)},
                               true},
                       Segment{{min(up.x + r, rectangle.up.x), max(up.y - r, rectangle.down.y)},
                               {min(up.x + r, rectangle.up.x), min(up.y + r, rectangle.up.y)},
                               false});
    return make_pair(Segment{{max(down.x - r, rectangle.down.x), max(down.y - r, rectangle.down.y)},
                             {max(up.x - r, rectangle.down.x), min(up.y + r, rectangle.up.y)},
                             true},
                     Segment{{min(down.x + r, rectangle.up.x), max(down.y - r, rectangle.down.y)},
                             {min(up.x + r, rectangle.up.x), min(up.y + r, rectangle.up.y)},
                             false});
  }
};
Segment rivers[maxN], nlogonia;
lli nlogoniaArea;

struct Node { lli marked, length; };
Node segtree[4*(maxX + 1)];
void fixNode(int i, int lo, int hi)
{
  if (segtree[i].marked > 0)
    segtree[i].length = hi - lo + 1;
  else if (lo != hi)
    segtree[i].length = segtree[2*i].length + segtree[2*i + 1].length;
  else
    segtree[i].length = 0;
}
void update(int qlo, int qhi, int value, int i = 1, int lo = nlogonia.down.y, int hi = nlogonia.up.y - 1)
{
  if (hi < qlo || lo > qhi) return;
  if (lo >= qlo && hi <= qhi)
  {
    segtree[i].marked += value;
    fixNode(i, lo, hi);
    return;
  }
  int mid = (lo + hi) >> 1;
  update(qlo, qhi, value, 2*i, lo, mid), update(qlo, qhi, value, 2*i + 1, mid + 1, hi);
  fixNode(i, lo, hi);
}
void printSpacing(int sz) { while (sz --) printf("   "); }
void dfs(int i = 1, int lo = nlogonia.down.y, int hi = nlogonia.up.y - 1, int depth = 0)
{
  printSpacing(depth);
  printf("[%d, %d] = %lld %lld\n", lo, hi, segtree[i].marked, segtree[i].length);
  if (lo == hi) return;
  int mid = (lo + hi) >> 1;
  dfs(2*i, lo, mid, depth + 1), dfs(2*i + 1, mid + 1, hi, depth + 1);
}
lli mm[maxX + 1];
void easyMark(int lo, int hi, int with)
{
  for (int i = lo; i <= hi; i ++)
    mm[i] += with;
}
lli easyQuery(int lo, int hi)
{
  lli got = 0;
  for (int i = lo; i <= hi; i ++)
    got += mm[i] > 0;
  return got;
}
bool can(int r)
{
  vector<Segment> segments;
  for (int i = 0; i < n; i ++)
  {
    pair<Segment, Segment> walls = rivers[i].getWalls(nlogonia, r);
    if (walls.first.down.x >= walls.second.down.x || walls.first.down.y >= walls.first.up.y || walls.second.down.y >= walls.second.up.y) continue;
    segments.push_back(walls.first), segments.push_back(walls.second);
  }
  sort(segments.begin(), segments.end());

  lli covered = 0, prvX = segments[0].down.x;
  for (int i = 0; i < segments.size(); i ++)
  {
    covered += segtree[1].length * (segments[i].down.x - prvX);
    if (segments[i].left)
      update(segments[i].down.y, segments[i].up.y - 1, 1);
    else
      update(segments[i].down.y, segments[i].up.y - 1, -1);
    prvX = segments[i].down.x;
  }
  // printf("%d - %lld %lld %lld\n", r, covered, nlogoniaArea, 100LL *covered / nlogoniaArea);
  return 100LL * covered >= p * nlogoniaArea;
}

int binarySearch()
{
  int lo = 1, hi = 1e5;
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    if (can(mid)) hi = mid;
    else lo = mid + 1;
  }
  return lo;
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    rivers[i].read();
  scanf("%d", &p);
  nlogonia.read();
  // nlogonia.print();
  nlogoniaArea = (nlogonia.up.x - nlogonia.down.x) * (nlogonia.up.y - nlogonia.down.y);

  int ans = binarySearch();
  printf("%d\n", ans);

  return 0;
}