#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli d, a;
struct Monster
{
  lli x, h;
  void read() { scanf("%lld %lld", &x, &h); }
  bool operator<(const Monster &other) const { return x < other.x; }
};
Monster monsters[maxN];

int main()
{
  while (scanf("%d %lld %lld", &n, &d, &a) != EOF)
  {
    for (int i = 0; i < n; i ++)
      monsters[i].read();
    sort(monsters, monsters+n);

    lli ans = 0, acc = 0;
    int prv = 0, j = 0, end = 0;

    for (int i = 0; i < n;)
    {
      lli rem = monsters[i].h - acc;
      DEBUG printf("\t\t%d %lld\n", i, rem);
      lli turns = max(0LL, rem / a + (rem % a != 0));
      ans += turns;
      acc += turns * a;

      prv = max(i, prv);
      while (prv + 1 < n && monsters[i].x + 2*d >= monsters[prv + 1].x) prv ++;
      j = max(i, j);
      while (j + 1 < n && monsters[i].x + 2*d >= monsters[j + 1].x && monsters[j + 1].h <= acc) j ++;

      if (j == n - 1) break;

      end = max(end, j + 1);
      while (end + 1 < n && monsters[j + 1].x + 2*d >= monsters[end + 1].x) end ++;

      for (int jj = prv + 1; jj <= end; jj ++)
        monsters[jj].h += acc;

      DEBUG printf("\t%d %d %d %d | %lld %lld %lld\n", i, prv, j, end, rem, acc, turns);
      i = j + 1;
    }
    printf("%lld\n", ans);
  }
  return 0;
}