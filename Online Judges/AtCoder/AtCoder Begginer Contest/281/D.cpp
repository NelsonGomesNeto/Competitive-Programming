#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
const lli inf = 1e18;
int n, k, d;
lli a[maxN];

lli memo[maxN][maxN][maxN];
lli solve2(int i = 0, int cnt = 0, int sumModD = 0)
{
  if (cnt == k) return sumModD == 0 ? 0 : -inf;
  if (i == n) return -inf;
  lli& ans = memo[i][cnt][sumModD];
  if (ans != -1) return ans;
  return ans = max(
    solve2(i + 1, cnt + 1, (sumModD + a[i] % d) % d) + a[i],
    solve2(i + 1, cnt, sumModD)
  );
}

bool visited[maxN][maxN][maxN];
struct State
{
  int i, cnt, sumModD; lli sum;
  const bool operator<(const State& other) const
  {
    return cnt > other.cnt || (cnt == other.cnt && sum < other.sum);
  }
};
lli solve()
{
  memset(visited, false, sizeof(visited));
  priority_queue<State> pq;
  pq.push(State{0, 0, 0, 0});
  while (!pq.empty())
  {
    State now = pq.top();
    pq.pop();
    if (now.cnt == k)
    {
      if (now.sumModD == 0) return now.sum;
      continue;
    }
    if (now.i == n || visited[now.i][now.cnt][now.sumModD]) continue;
    visited[now.i][now.cnt][now.sumModD] = true;

    pq.push(State{now.i + 1, now.cnt + 1, (now.sumModD + (int)a[now.i] % d) % d, now.sum + a[now.i]});
    pq.push(State{now.i + 1, now.cnt, now.sumModD, now.sum});
  }
  return -1;
}

int main()
{
  while (~scanf("%d %d %d", &n, &k, &d))
  {
    for (int i = 0; i < n; ++i)
      scanf("%lld", &a[i]);

    memset(memo, -1, sizeof(memo));
    lli ans = max(-1LL, solve2());
    printf("%lld\n", ans);
  }
  return 0;
}
