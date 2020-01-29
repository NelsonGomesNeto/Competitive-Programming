#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
char s[maxN + 1];
bool allowed[256];
int r[maxN];

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    memset(allowed, false, sizeof(allowed));
    scanf(" %s", s);
    for (int i = 0; i < k; i ++)
    {
      char prv, a; scanf("%c%c", &prv, &a);
      allowed[a] = true;
    }

    r[n - 1] = allowed[s[n - 1]] ? n : n - 1;
    for (int i = n - 2; i >= 0; i --)
      r[i] = allowed[s[i]] ? r[i + 1] : i;

    lli ans = 0;
    for (int i = 0; i < n; i ++)
      ans += r[i] - i;
    printf("%lld\n", ans);
  }
  return 0;
}
