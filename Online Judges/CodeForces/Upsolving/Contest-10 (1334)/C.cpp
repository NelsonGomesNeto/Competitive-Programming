#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
bool done[maxN];
pair<lli, lli> monsters[maxN];

int prv(int i)
{
  return i - 1 < 0 ? n - 1 : i - 1;
}
int nxt(int i)
{
  return (i + 1) % n;
}

struct Node
{
  lli saved; int index;
  bool operator<(const Node &other) const
  {
    return saved > other.saved;
  }
};

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%lld %lld", &monsters[i].first, &monsters[i].second);
      done[i] = false;
    }

    priority_queue<Node> pq;
    for (int i = 0; i < n; i++)
      pq.push({min(monsters[prv(i)].second, monsters[i].first), i});

    lli ans = 0;
    while (!pq.empty())
    {
      int i = pq.top().index; pq.pop();
      if (done[i]) continue;
      done[i] = true;
      ans += monsters[i].first;
      while (done[i] && !done[nxt(i)])
      {
        monsters[nxt(i)].first -= monsters[i].second;
        if (monsters[nxt(i)].first <= 0)
          done[nxt(i)] = true;
        else
          pq.push({0, nxt(i)});
        i = nxt(i);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
