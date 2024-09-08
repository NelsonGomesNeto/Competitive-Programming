#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;
const int maxN = 500; int n;
lli a[maxN];

vector<lli> xs;
struct Op
{
  char op; lli x;
  void read()
  {
    scanf(" %c", &op);
    if (op == '+')
    {
      scanf("%lld", &x);
      xs.push_back(x);
    }
  }
};
Op ops[maxN];

lli memo[maxN][2*maxN*maxN];
lli solve(int i = 0, priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, greater<pair<lli, lli>>> pq = priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, greater<pair<lli, lli>>>(), lli sum = 0, lli heheSum = 0)
{
  if (i == n) return sum;

  lli &ans = memo[i][heheSum];
  if (ans != -1) return ans;

  // if (memo[i].count(sum)) return memo[i][sum];
  // lli &ans = memo[i][sum];

  ans = solve(i + 1, pq, sum, heheSum);

  if (ops[i].op == '+')
  {
    pq.push({ops[i].x, i});
    sum = (sum + ops[i].x) % mod;
    heheSum += i + lower_bound(xs.begin(), xs.end(), ops[i].x) - xs.begin();
  }
  else if (!pq.empty())
  {
    sum = (sum - pq.top().first + mod) % mod;
    heheSum -= pq.top().second + lower_bound(xs.begin(), xs.end(), pq.top().first) - xs.begin();
    pq.pop();
  }
  ans = (ans + solve(i + 1, pq, sum, heheSum)) % mod;

  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    xs.clear();
    for (int i = 0; i < n; i++)
      ops[i].read();
    sort(xs.begin(), xs.end());
    xs.resize(distance(xs.begin(), unique(xs.begin(), xs.end())));

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
