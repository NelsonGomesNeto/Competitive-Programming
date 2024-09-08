#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n;
char s[maxN + 1];
int v[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    scanf(" %s", s);
    int sum = 0;
    for (int i = 0; i < n; i ++)
      sum += v[i] = s[i] == '(' ? 1 : -1;
    if (sum != 0)
    {
      printf("-1\n");
      continue;
    }

    lli ans = 0;
    for (int i = 0; i < n; i ++)
    {
      if (s[i] == ')')
      {
        int j = i, op = -1;
        while (j + 1 < n && op + v[j + 1] != 0) op += v[++ j];
        j ++;
        DEBUG printf("\t) %d - %d\n", i, j);
        if (j < n)
        {
          ans += j - i + 1;
          i = j;
        }
        else
        {
          ans = -1;
          break;
        }
      }
      else
      {
        int j = i, op = 1;
        while (j + 1 < n && op + v[j + 1] != 0) op += v[++ j];
        j ++;
        DEBUG printf("\t( %d - %d\n", i, j);
        if (j < n)
        {
          // ans += j - i + 1;
          i = j;
        }
        else
        {
          ans = -1;
          break;
        }
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
