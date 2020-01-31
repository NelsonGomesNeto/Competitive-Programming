#include <bits/stdc++.h>
#define DEBUG if(0)
#define HERE DEBUG printf("here\n");
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5, maxM = 8, inf = 1e9 + 1; int n, m;
vector<int> a[maxN];
int masks[1 << maxM];

struct Ans
{
  int value, i, j;
  void print() { printf("%d %d\n", i + 1, j + 1); }
  bool operator<(const Ans &other) const { return value < other.value; }
  bool operator>(const Ans &other) const { return value > other.value; }
  bool operator!=(const Ans &other) const { return value != other.value; }
};
Ans nil = {-1, 0, 0};

Ans can(int x)
{
  memset(masks, -1, sizeof(masks));
  for (int i = 0; i < n; i ++)
  {
    int curr = 0;
    for (int j = 0; j < m; j ++)
      curr |= (a[i][j] >= x) << j;
    masks[curr] = i;
  }

  for (int i = 0, end = 1 << maxM; i < end; i ++)
    for (int j = 0; j < end; j ++)
      if (masks[i] != -1 && masks[j] != -1 && (i | j) == (1 << m) - 1)
        return Ans{x, masks[i], masks[j]};
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
