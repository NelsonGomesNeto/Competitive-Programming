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
    /*
      For each pair XO or OX: we can calculate the amount of substrings that will contain them
    */
    for (int i = 0; i < n; i++)
    {
      while (i < n && s[i] != 'X' && s[i] != 'O') i++;

      if (i < n)
      {
        char cu = s[i];
        char op = s[i] == 'O' ? 'X' : 'O';

        int j = i + 1;
        while (j < n && s[j] != op) j++;

        i = j - 1;
        while (i >= 0 && s[i] != cu) i--;

        if (j < n)
        {
          DEBUG printf("\t%d %d\n", i, j);
          lli l = i + 1, r = n - j;
          ans = (ans + l * r % mod) % mod;
        }

        i = j - 1;
      }
    }

    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}