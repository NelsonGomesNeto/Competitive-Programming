#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10, maxG = 5; int n = 10;
char s[maxN + 1];

int main()
{
  DEBUG {
    for (int i = 0; i < 10; i++)
    {
      int aleft = (9 - i) >> 1; // even
      int bleft = (9 - i + 1) >> 1; // odd
      printf("%d %d %d\n", i, aleft, bleft);
    }
  }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", s);

    int ans = 10;
    for (int mask = 0, end = 1 << n; mask < end; mask++)
    {
      bool valid = true;
      for (int i = 0; i < n; i++)
        if (s[i] != '?' && !((mask & (1 << i)) ? s[i] == '1' : s[i] == '0'))
          valid = false;
      if (!valid)
        continue;

      DEBUG printf("hehe %d\n", mask);
      int now = 10, a = 0, b = 0;
      for (int i = 0; i < n; i++)
      {
        int aleft = (9 - i) >> 1; // even
        int bleft = (9 - i + 1) >> 1; // odd

        if (i & 1)
          b += (mask >> i) & 1;
        else
          a += (mask >> i) & 1;

        if (a + aleft < b || b + bleft < a)
        {
          now = i + 1;
          break;
        }
      }
      ans = min(ans, now);
    }
    printf("%d\n", ans);
  }
  return 0;
}
