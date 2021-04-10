#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, a, b;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &a, &b);
    scanf(" %s", s);
    n = strlen(s);

    for (int i = 0; i < n; i++)
      a -= s[i] == '0', b -= s[i] == '1';

    bool can = true;
    for (int i = 0, j = n - 1; i < j; i++, j--)
      if (s[i] == '?' && s[j] != '?')
      {
        s[i] = s[j];
        a -= s[i] == '0', b -= s[i] == '1';
      }
      else if (s[i] != '?' && s[j] == '?')
      {
        s[j] = s[i];
        a -= s[j] == '0', b -= s[j] == '1';
      }

    for (int i = 0, j = n - 1; i < j; i++, j--)
      if (s[i] == '?' && s[j] == '?')
      {
        if (a >= b && a >= 2)
          s[i] = s[j] = '0', a -= 2;
        else if (b >= a && b >= 2)
          s[i] = s[j] = '1', b -= 2;
      }
    if ((n & 1) && s[n >> 1] == '?')
    {
      if (a) s[n >> 1] = '0', a--;
      else s[n >> 1] = '1', b--;
    }

    for (int i = 0, j = n - 1; i < n; i++, j--)
      can &= s[i] != '?' && s[i] == s[j];
    can &= (a == 0) && (b == 0);

    if (!can) printf("-1\n");
    else printf("%s\n", s);
  }
  return 0;
}
