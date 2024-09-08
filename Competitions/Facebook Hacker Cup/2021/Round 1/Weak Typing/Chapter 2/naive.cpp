#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8e5; int n;
const lli mod = 1e9 + 7;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", s);

    lli ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = i; j < n; j++)
      {
        char prv = '\0';
        for (int k = i; k <= j; k++)
        {
          ans += (s[k] == 'O' && prv == 'X') || (s[k] == 'X' && prv == 'O');
          if (ans >= mod) ans -= mod;
          prv = (s[k] == 'O' || s[k] == 'X') ? s[k] : prv;
        }
      }

    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}