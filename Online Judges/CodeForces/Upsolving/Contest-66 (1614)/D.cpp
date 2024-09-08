#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const int maxX = 5e6;
int a[maxN];
int cnt[maxX + 1];

int main()
{
  int hehe = 0;
  while (~scanf("%d", &n))
  {
    if (hehe++)
    {
      fill(cnt, cnt+maxX+1, 0);
    }

    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      cnt[a[i]]++;
    }

    lli ans = 0;
    for (int i = 1; i <= maxX; i++)
    {
      lli sum = (lli)i * cnt[i];
      for (int j = 2*i; j <= maxX; j += i)
        sum += (lli)j * cnt[j];
      ans = max(ans, sum);
    }
    printf("%lld\n", ans);
  }

  return 0;
}