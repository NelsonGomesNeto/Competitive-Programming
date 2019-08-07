#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e6;
char s[maxN + 1];
int cnt[3];

int main()
{
  while (scanf("%s", s) != EOF)
  {
    lli ans = 0; int now = 0; cnt[0] = 1, cnt[1] = cnt[2] = 0;
    for (int i = 0; s[i]; i ++)
    {
      if (s[i] >= '0' && s[i] <= '9')
      {
        now = (now + s[i] - '0') % 3;
        ans += cnt[now] ++;
      }
      else
        cnt[0] = 1, cnt[1] = cnt[2] = now = 0;
    }
    printf("%lld\n", ans);
  }

  return(0);
}