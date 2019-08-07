#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int p, v;

struct Point
{
  int x, y, value;
  bool operator<(const Point &p) const
  {
    return(x < p.x || (x == p.x && y < p.y));
  }
};
Point points[2*maxN];
int segtree[4*(2*maxN + 1)], highest;
int query(int qlo, int qhi, int i = 1, int lo = 0, int hi = highest)
{
  if (hi < qlo || lo > qhi) return(0);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi));
}
void update(int pos, int value, int i = 1, int lo = 0, int hi = highest)
{
  if (lo > pos || hi < pos) return;
  if (lo == hi)
  {
    segtree[i] += value;
    return;
  }
  int mid = (lo + hi) >> 1;
  update(pos, value, 2*i, lo, mid), update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  scanf("%d %d", &p, &v);
  map<int, int> allY;
  for (int i = 0; i < p + v; i ++)
  {
    scanf("%d %d", &points[i].x, &points[i].y);
    points[i].value = i < p ? i + 1 : -1;
    allY[points[i].y] = 0;
  }
  for (auto &i: allY)
  {
    i.second = highest;
    highest += 2;
  }
  for (int i = 0; i < p + v; i ++) points[i].y = allY[points[i].y];

  sort(points, points+p+v);

  lli ans = 0;
  for (int i = 0; i < p + v; i ++)
  {
    if (points[i].value == -1) // part of the fence
    {
      update(points[i].y, 1);
      update(points[++ i].y + 1, -1);
    }
    else ans += !(query(0, points[i].y + 1) & 1) ? points[i].value : 0;
  }
  printf("%lld\n", ans);

  return(0);
}