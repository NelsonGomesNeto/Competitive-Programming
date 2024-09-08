#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Ideas:
  (Li, 0) -> (Li + W, Hi)
  Since all room has a wall at y == 0:
  So every room will be connected if: Li <= Lj <= Li + W
  Since W is fixed for all rooms: there are only three possibilities
    1: Li + W < Lj

         |    |
    2: | |  | | room i is smaller than room j
       |_|__|_|

       |    |
    3: | |  | | room i is bigger than room j
       |_|__|_|

  P0 = 2*W + 2*H0

  if it connects with the previous room:
    Pdelta =
      horizontal: 2*(Lj - Li)
      vertical: room i smaller than room j ? 2*(Hj - Hi) : 0

  above is right, but you've got to consider the highest previous room that is connected
*/

const int maxN = 1e6; int n, k; lli w;
const lli mod = 1e9 + 7;
lli al, bl, cl, dl, ah, bh, ch, dh;
struct Room
{
  lli l, h;
};
Room rooms[maxN];
lli p[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %lld", &n, &k, &w);

    for (int i = 0; i < k; i++) scanf("%lld", &rooms[i].l);
    scanf("%lld %lld %lld %lld", &al, &bl, &cl, &dl);
    for (int i = k; i < n; i++) rooms[i].l = (al * rooms[i - 2].l + bl * rooms[i - 1].l + cl) % dl + 1;

    for (int i = 0; i < k; i++) scanf("%lld", &rooms[i].h);
    scanf("%lld %lld %lld %lld", &ah, &bh, &ch, &dh);
    for (int i = k; i < n; i++) rooms[i].h = (ah * rooms[i - 2].h + bh * rooms[i - 1].h + ch) % dh + 1;

    lli ans = 1;
    p[0] = (2LL*w % mod + 2LL*rooms[0].h % mod) % mod;
    for (int i = 1; i < n; i++)
      if (rooms[i].l > rooms[i - 1].l + w)
        p[i] = (p[i - 1] + 2LL*w % mod + 2LL*rooms[i].h % mod) % mod;
      else
      {
        int j = i;
        lli highest = 0;
        while (j - 1 >= 0 && rooms[i].l <= rooms[j - 1].l + w)
          highest = max(highest, rooms[--j].h);

        p[i] = (p[i - 1] + 2LL*(rooms[i].l - rooms[i - 1].l) % mod) % mod;
        if (rooms[i].h > highest)
          p[i] = (p[i] + 2LL*(rooms[i].h - highest) % mod) % mod;
      }

    for (int i = 0; i < n; i++)
      ans = (ans * p[i]) % mod;

    DEBUG {
      printf("\n");
      printf("W: %lld\n", w);
      printf("L: ");
      for (int i = 0; i < n; i++) printf("%lld%c", rooms[i].l, i < n - 1 ? ' ' : '\n');
      printf("H: ");
      for (int i = 0; i < n; i++) printf("%lld%c", rooms[i].h, i < n - 1 ? ' ' : '\n');
      printf("P: ");
      for (int i = 0; i < n; i++) printf("%lld%c", p[i], i < n - 1 ? ' ' : '\n');
    }

    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}