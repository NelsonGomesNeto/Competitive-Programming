#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, k;
struct Section
{
  lli curr, lo, hi;
};
Section sections[maxN];

lli as, bs, cs, ds;
lli ax, bx, cx, dx;
lli ay, by, cy, dy;

void printEverything()
{
  if (n >= 100) return;
  DEBUG {
    printf("S: ");
    for (int i = 0; i < n; i++) printf("%lld%c", sections[i].curr, i < n - 1 ? ' ' : '\n');
    printf("lo: ");
    for (int i = 0; i < n; i++) printf("%lld%c", sections[i].lo, i < n - 1 ? ' ' : '\n');
    printf("hi: ");
    for (int i = 0; i < n; i++) printf("%lld%c", sections[i].hi, i < n - 1 ? ' ' : '\n');
  }
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < k; i++)
      scanf("%lld", &sections[i].curr);
    scanf("%lld %lld %lld %lld", &as, &bs, &cs, &ds);
    for (int i = k; i < n; i++)
      sections[i].curr = (as * sections[i - 2].curr + bs * sections[i - 1].curr + cs) % ds;

    for (int i = 0; i < k; i++)
      scanf("%lld", &sections[i].lo);
    scanf("%lld %lld %lld %lld", &ax, &bx, &cx, &dx);
    for (int i = k; i < n; i++)
      sections[i].lo = (ax * sections[i - 2].lo + bx * sections[i - 1].lo + cx) % dx;

    for (int i = 0; i < k; i++)
      scanf("%lld", &sections[i].hi);
    scanf("%lld %lld %lld %lld", &ay, &by, &cy, &dy);
    for (int i = k; i < n; i++)
      sections[i].hi = (ay * sections[i - 2].hi + by * sections[i - 1].hi + cy) % dy;
    for (int i = 0; i < n; i++)
      sections[i].hi += sections[i].lo;

    
    printEverything();

    lli ans = 0, leftOver = 0;
    for (int hehe = 0; hehe < 4; hehe++)
      for (int i = 0; i < n; i++)
      {
        if (sections[i].curr > sections[i].hi)
        {
          leftOver += sections[i].curr - sections[i].hi;
          ans += sections[i].curr - sections[i].hi;
          sections[i].curr = sections[i].hi;
        }
        if (sections[i].curr < sections[i].lo)
        {
          leftOver -= sections[i].lo - sections[i].curr;
          ans += sections[i].lo - sections[i].curr;
          sections[i].curr = sections[i].lo;
        }
      }
    for (int hehe = 0; hehe < 4; hehe++)
      for (int i = 0; i < n; i++)
        if (leftOver > 0 && sections[i].curr < sections[i].hi)
        {
          lli changed = min(leftOver, sections[i].hi - sections[i].curr);
          sections[i].curr += changed;
          ans += changed;
          leftOver -= changed;
        }
        else if (leftOver < 0 && sections[i].curr > sections[i].lo)
        {
          lli changed = min(-leftOver, sections[i].curr - sections[i].lo);
          sections[i].curr -= changed;
          ans += changed;
          leftOver += changed;
        }

    bool valid = leftOver == 0;
    for (int i = 0; i < n; i++)
      if (sections[i].curr < sections[i].lo || sections[i].curr > sections[i].hi)
        valid = false;
    ans = !valid ? -1: ans;
    DEBUG printf("leftOver: %lld\n", leftOver);

    printf("Case #%d: %lld\n", tt, ans >> 1LL);

    printEverything();
    DEBUG {
      printf("\n");
    }
  }
  return 0;
}