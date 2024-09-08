#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
pair<lli, lli> monsters[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld %lld", &monsters[i].first, &monsters[i].second);

    lli ans = 0;
    lli minimumBulletsSaved = 1e15;
    for (int i = 0; i < n; i++)
    {
      ans += monsters[i].first;
      lli bulletsSaved = min(monsters[i].second, monsters[(i + 1) % n].first);
      ans -= bulletsSaved;
      minimumBulletsSaved = min(minimumBulletsSaved, bulletsSaved);
    }
    ans += minimumBulletsSaved;
    printf("%lld\n", ans);
  }
  return 0;
}