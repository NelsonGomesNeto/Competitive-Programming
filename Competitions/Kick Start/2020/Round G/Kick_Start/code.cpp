#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
char s[maxN + 1];

int r[maxN + 1];
char start[6] = "START";
bool hasStart(int i)
{
  if (i + 4 >= n) return false;
  for (int j = 0; j < 5; j++)
    if (s[i + j] != start[j])
      return false;
  return true;
}

char kick[6] = "KICK";
bool hasKick(int i)
{
  if (i + 3 >= n) return false;
  for (int j = 0; j < 4; j++)
    if (s[i + j] != kick[j])
      return false;
  return true;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", s);
    n = strlen(s);

    r[n] = 0;
    for (int i = n - 1; i >= 0; i--)
      r[i] = r[i + 1] + hasStart(i);

    int ans = 0;
    for (int i = 0; i < n; i++)
      if (hasKick(i))
        ans += r[i];

    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}