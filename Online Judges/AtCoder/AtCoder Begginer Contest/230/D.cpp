#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; int d;
struct Wall
{
  int l, r;
  void read() { scanf("%d %d", &l, &r); }
  bool operator<(const Wall &other) const { return r < other.r; }
};
Wall walls[maxN];

int main()
{
  while (~scanf("%d %d", &n, &d))
  {
    for (int i = 0; i < n; i++)
      walls[i].read();
    sort(walls, walls+n);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      int j = i;
      while (j + 1 < n && walls[j + 1].l - walls[i].r + 1 <= d)
        j++;

      ans++;

      i = j;
    }

    printf("%d\n", ans);
  }
  return 0;
}