#include <bits/stdc++.h>
#define DEBUG if(0)
#define HERE DEBUG printf("here\n");
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5, maxM = 8, inf = 1e9 + 1; int n, m;
vector<int> a[maxN];
struct Mask
{
  int revMask, mask, index;
  bool operator<(const Mask &other) const { return revMask < other.revMask; }
};
Mask masks[maxN];

struct Ans
{
  int value, i, j;
  void print() { printf("%d %d\n", i + 1, j + 1); }
  bool operator<(const Ans &other) const { return value < other.value; }
  bool operator>(const Ans &other) const { return value > other.value; }
  bool operator!=(const Ans &other) const { return value != other.value; }
};
Ans nil = {-1, 0, 0};

int findLastZeroPos(int at, int lo, int hi)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (!(masks[mid].mask & (1 << at))) lo = mid;
    else hi = mid - 1;
  }
  return masks[lo].mask & (1 << at) ? lo - 1 : lo;
}
int match(int i, int at = 0, int lo = 0, int hi = n - 1)
{
  if (at == m) return lo;

  int pos = -1, lastZeroPos = findLastZeroPos(at, lo, hi);
  if (lastZeroPos >= lo && (masks[i].mask & (1 << at)))
    pos = match(i, at + 1, lo, lastZeroPos);
  if (lastZeroPos + 1 <= hi)
    pos = max(pos, match(i, at + 1, lastZeroPos + 1, hi));

  return pos;
}
Ans can(int x)
{
  for (int i = 0; i < n; i ++)
  {
    masks[i].revMask = masks[i].mask = 0;
    for (int j = 0, jj = m - 1; j < m; j ++, jj --)
      masks[i].revMask |= (a[i][j] >= x) << jj, masks[i].mask |= (a[i][j] >= x) << j;
    masks[i].index = i;
  }
  sort(masks, masks+n);

  for (int i = n - 1; i >= 0; i --)
  {
    int j = match(i);
    if (j != -1)
      return Ans{x, masks[i].index, masks[j].index};
  }
  return nil;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
    {
      a[i].clear();
      a[i].resize(m);
      for (int j = 0; j < m; j ++)
        scanf("%d", &a[i][j]);
    }

    Ans ans = nil;
    int lo = 0, hi = inf;
    while (lo < hi)
    {
      int mid = ((lli)lo + (lli)hi + 1) >> 1LL;
      if (can(mid) != nil) lo = mid;
      else hi = mid - 1;
    }
    ans = can(lo);
    DEBUG printf("%d - ", ans.value);
    ans.print();
  }
  return 0;
}
