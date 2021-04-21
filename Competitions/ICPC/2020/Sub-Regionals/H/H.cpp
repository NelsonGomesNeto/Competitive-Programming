#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, k; lli a, b;
lli p[maxN];

lli memo[maxN][maxN];
lli chooseAll(int i = 0, int chosen = 0)
{
  if (chosen == k) return 1;
  if (i == n) return 0;
  lli &ans = memo[i][chosen];
  if (ans != -1) return ans;
  return ans = chooseAll(i + 1, chosen + 1) + chooseAll(i + 1, chosen);
}
lli f(lli limit, int i = 0, int chosen = 0, lli sum = 0)
{
  if (sum > limit) return 0;
  if (chosen == k) return sum <= limit;
  if (i == n) return 0;

  lli ans = 0;
  if (sum + 2*p[i] - 1 <= limit)
    ans = chooseAll(i, chosen);
  else
    ans = f(limit, i + 1, chosen + 1, sum + p[i])
        + f(limit, i + 1, chosen, sum);
  return ans;
}
lli f2(lli available, int i = 0, int chosen = 0)
{
  if (chosen == k) return 1;
  if (i == n) return 0;

  lli ans = 0;
  if (p[i] <= available)
    ans = f2(available - p[i], i + 1, chosen + 1) + chooseAll(i + 1, chosen);
  else
    ans = f2(available, i + 1, chosen);
  return ans;
}

int main()
{
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++)
    scanf("%lld", &p[i]);
  scanf("%lld %lld", &a, &b);
  sort(p, p+n, greater<lli>());

  memset(memo, -1, sizeof(memo));
  chooseAll();

  lli ans = f2(b) - f2(a - 1);
  printf("%lld\n", ans);

  return 0;
}