#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4; int n; lli d, c, m;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld %lld %lld", &n, &d, &c, &m);
    scanf(" %s", s);

    bool can = true;
    for (int i = 0; i < n; i++)
    {
      if (s[i] == 'D')
      {
        if (d == 0)
        {
          can = false;
          break;
        }
        d--, c += m;
      }
      else
      {
        if (c == 0)
        {
          for (int j = i + 1; j < n; j++)
            if (s[j] == 'D')
              can = false;
          break;
        }
        c--;
      }
    }

    printf("Case #%d: %s\n", tt, can ? "YES" : "NO");
  }
  return 0;
}