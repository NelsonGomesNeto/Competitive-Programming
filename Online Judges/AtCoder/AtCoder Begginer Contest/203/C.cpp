#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli k;
pair<lli, lli> friends[maxN];

int main()
{
  while (~scanf("%d %lld", &n, &k))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld %lld", &friends[i].first, &friends[i].second);
    sort(friends, friends+n);

    lli ans = 0, coins = k;
    for (int i = 0; i < n; i++)
    {
      lli required = friends[i].first - ans;
      if (required > coins)
        break;

      coins -= required;

      int j = i;
      lli got = friends[i].second;
      while (j + 1 < n && friends[j + 1].first == friends[i].first)
      {
        j++;
        got += friends[j].second;
      }

      ans = friends[i].first;
      coins += got;

      i = j;
    }
    ans += coins;

    printf("%lld\n", ans);
  }
  return 0;
}