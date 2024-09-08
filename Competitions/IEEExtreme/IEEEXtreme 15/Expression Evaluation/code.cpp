#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
const lli mod = 1e9 + 7;
char s[maxN + 1]; int n;
bool isDigit[256];

lli solve(int i = 0)
{
  if (isDigit[s[i]])
  {
    int j = i;
    while (j + 1 < n && isDigit[s[j + 1]]) j++;
    lli a = readNumber(i, j);

    j++;

    if (j == n) return a;

    if (s[j] == '(') return LONG_LONG_MIN;

    if (s[j] == ')') return a;

    char op = s[j]; // +*-

    int k = j + 1;

    if (isDigit[s[k]])
    {
      int p = k;
      while (p + 1 < n && isDigit[s[p + 1]]) p++;
      lli b = readNumber();

      
    }
  }

  if (s[i] == '(')
    return solve(i + 1);

  if (s[i] == ')')
  {

  }
}

int main()
{
  for (int i = '0'; i <= '9'; i++) isDigit[i] = 1;

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", s);
    n = strlen(s);

    lli ans = solve();
    if (ans == LONG_LONG_MIN) printf("invalid");
    else printf("%lld\n", ans);
  }
  return 0;
}