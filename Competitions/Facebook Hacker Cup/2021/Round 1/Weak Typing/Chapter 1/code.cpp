#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8e5; int n;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", s);

    lli ans = 0;
    char prv = '\0';
    for (int i = 0; i < n; i++)
    {
      ans += (s[i] == 'O' && prv == 'X') || (s[i] == 'X' && prv == 'O');
      prv = (s[i] == 'O' || s[i] == 'X') ? s[i] : prv;
    }

    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}