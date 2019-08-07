#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  Divide and Conquer FOR THE WIN
  You have two options:
    Horizontal:
      Fill the whole fence from left to right
      At first, that will be done min(a1, a2, ..., an) times
      This will split a segment into many others
    Vertical:
      Fill each plank, so: right - left + 1 times
      This will end a segment

  You start by the whole fence: lo = 0, hi = n - 1, currentHeight = 0
    vertical choice will always be: hi - lo + 1
    horizontal choice will be: min(a1, a2, ..., an) - currentHeight
      But you will end up splitting this segment into others, since you
      can no longer fill the next heights with a single stroke
      For each new segment: horizontal += recursiveCall(newLo, newHi, min(a1, a2, ..., an))
    return(min(vertical, horizontal))
*/

const int maxN = 5e3; int n;
const lli inf = 2e9;
lli a[maxN];

lli segtree[4*maxN];
void build(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo >= hi)
  {
    segtree[i] = a[lo];
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
  segtree[i] = min(segtree[2*i], segtree[2*i + 1]);
}
lli query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo > qhi || hi < qlo) return(inf);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(min(query(qlo, qhi, 2*i, lo, mid), query(qlo, qhi, 2*i + 1, mid + 1, hi)));
}
void update(int pos, lli value, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo > pos || hi < pos) return;
  if (lo >= hi)
  {
    segtree[i] = a[lo] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  update(pos, value, 2*i, lo, mid), update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = min(segtree[2*i], segtree[2*i + 1]);
}

lli minimumHeight(int lo, int hi)
{
  return(query(lo, hi));
  lli h = inf;
  for (int i = lo; i <= hi; i ++) h = min(h, a[i]);
  return(h);
}

lli solve(int lo = 0, int hi = n - 1, lli h = 0)
{
  lli newHeight = minimumHeight(lo, hi), horizontal = 0, vertical = hi - lo + 1;
  // printf("%d %d %lld\n", lo, hi, newHeight);
  horizontal += newHeight - h;
  for (int i = lo; i <= hi; i ++)
  {
    if (a[i] <= newHeight) continue;
    int end = i + 1; while (end <= hi && newHeight < a[end]) end ++;
    horizontal += solve(i, end - 1, newHeight);
    i = end - 1;
  }
  return(min(horizontal, vertical));
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%lld", &a[i]);
  build();

  lli ans = solve();
  printf("%lld\n", ans);

  return(0);
}