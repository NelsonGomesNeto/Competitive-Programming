#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli r1, c1, r2, c2;
  while (scanf("%lld %lld %lld %lld", &r1, &c1, &r2, &c2) != EOF)
  {
    if (r1 > r2) swap(r1, r2), swap(c1, c2);

    lli dr = abs(r2 - r1), dc = abs(c2 - c1);
    DEBUG printf("\t%lld %lld | %lld %lld | %lld %lld\n", r1, c1, r2, c2, dr, dc);

    int ans = 0;
    if (dr + dc == 0) ans = 0;
    else if (!(((r2 + c2) - (r1 - c1)) & 1) || !(((r1 + c1) - (r2 - c2)) & 1)) ans = 2;
    else ans = 3;

    for (int i = -11; i <= 11; i++)
      for (int j = -11; j <= 11; j++)
      {
        lli nr = i + r1, nc = j + c1;
        if (r1 + c1 == nr + nc
          || r1 - c1 == nr - nc
          || abs(r1 - nr) + abs(c1 - nc) <= 3)
        {
          if (nr + nc == r2 + c2 || nr - nc == r2 - c2)
            ans = min(ans, 2 - 1 + (i || j));
          if (nr == r2 && nc == c2)
            ans = min(ans, 1 - 1 + (i || j));

          for (int ii = -11; ii <= 11; ii++)
            for (int jj = -11; jj <= 11; jj++)
            {
              lli nnr = ii + nr, nnc = jj + nc;
              if (nr + nc == nnr + nnc
                || nr - nc == nnr - nnc
                || abs(nnr - nr) + abs(nnc - nc) <= 3)
              {
                if (nnr == r2 && nnc == c2)
                  ans = min(ans, 2 - 1 - 1 + (i || j) + (ii || jj));
              }
            }
        }
      }

    printf("%d\n", ans);
  }
  return 0;
}