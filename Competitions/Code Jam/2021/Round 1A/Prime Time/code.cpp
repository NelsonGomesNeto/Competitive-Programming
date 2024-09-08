#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxM = 95; int m;
struct Card
{
  int p, n;
  void read() { scanf("%d %d", &p, &n); }
  // bool operator<(const Card &other) const { return n < other.n || (n == other.n && p < other.p); }
};
Card cards[maxM];
lli totalSum = 0;

map<lli, lli> memo[maxM];
lli solve(int i = 0, lli sum = totalSum, lli mul = 1)
{
  if (sum <= mul)
    return sum == mul ? mul : 0;
  if (i == m)
    return 0;
  if (memo[i].count(mul))
    return memo[i][mul];

  lli &ans = memo[i][mul];
  ans = 0;
  for (int j = 0; j <= cards[i].n && sum >= mul; j++)
  {
    ans = max(ans, solve(i + 1, sum, mul));
    sum -= cards[i].p;
    mul *= cards[i].p;
  }
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &m);
    totalSum = 0;
    for (int i = 0; i < m; i++)
    {
      cards[i].read();
      totalSum += cards[i].p * cards[i].n;
      memo[i].clear();
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine e(seed);
    shuffle(cards, cards+m, e);

    // sort(cards, cards+m);
    // reverse(cards, cards+m);

    lli ans = solve();
    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}