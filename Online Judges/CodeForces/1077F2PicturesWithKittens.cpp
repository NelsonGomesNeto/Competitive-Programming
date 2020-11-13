#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n, k, x;
const lli inf = 1e15;
int a[maxN];

template<class T>
struct MinMaxQueue
{
  deque<T> maxdq, mindq; queue <T> q;
  MinMaxQueue() { }
  void clear()
  {
    maxdq.clear(), mindq.clear();
    while (!q.empty()) q.pop();
  }
  void push(T value)
  {
    while (!maxdq.empty() && maxdq.back() < value)
      maxdq.pop_back();
    while (!mindq.empty() && mindq.back() > value)
      mindq.pop_back();
    q.push(value), maxdq.push_back(value); // mindq.push_back(value);
  }
  T max() { assert(!maxdq.empty()); return maxdq.front(); }
  T min() { assert(!mindq.empty()); return mindq.front(); }
  T front() { assert(!q.empty()); return q.front(); }
  void pop()
  {
    if (q.empty())
      return;
    if (!maxdq.empty() && maxdq.front() == q.front())
      maxdq.pop_front();
    if (!mindq.empty() && mindq.front() == q.front())
      mindq.pop_front();
    q.pop();
  }
  size_t size() { return q.size(); }
  bool empty() { return q.empty(); }
};

MinMaxQueue<pair<lli, int>> mmq[maxN + 1];
lli solve()
{
  for (int i = 0; i <= x; i++)
  {
    mmq[i].clear();
    mmq[i].push({0, n});
  }

  for (int i = n - 1; i >= 0; i--)
    for (int posted = 0; posted < x; posted++)
    {
      // get maximum from 1 to min(n - i, k)
      while (!mmq[posted + 1].empty() && mmq[posted + 1].front().second > i + k)
        mmq[posted + 1].pop();
      lli curr = mmq[posted + 1].empty() ? -inf : mmq[posted + 1].max().first;

      // for (int j = 1, end = min(n - i, k); j <= end; j++)
      //   curr = max(curr, memo[i + j][posted + 1]);
      // memo[i][posted] = a[i] + curr;

      mmq[posted].push({curr + a[i], i});
    }

  lli ans = -inf;
  while (!mmq[0].empty() && mmq[0].front().second >= k)
    mmq[0].pop();
  while (!mmq[0].empty())
  {
    ans = max(ans, mmq[0].front().first);
    mmq[0].pop();
  }
  return ans;
}

int main()
{
  while (scanf("%d %d %d", &n, &k, &x) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    lli ans = solve();
    ans = ans < 0 ? -1 : ans;
    printf("%lld\n", ans);
  }
  return 0;
}