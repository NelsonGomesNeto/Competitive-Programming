#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

bitset<200> smask, emask;
unordered_set<bitset<200>> visited;
lli startTime;
bool stop;
// lli clock()
// {
//   chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
// }
int dfs(bitset<200> u)
{
  if (stop)
    return 1e9;
  // if (clock() - startTime > 1000000)
  // {
  //   stop = true;
  //   return 1e9;
  // }
  if (u == emask) return 0;
  if (visited.count(u)) return 1e9;
  visited.insert(u);

  int ans = 1 + min(dfs(~u), dfs(u << 1LL));
  return ans;
}
int getMsb(bitset<200> x)
{
  for (int i = 199; i >= 0; i--)
    if (x[i])
      return i;
  return 0;
}
bitset<200> flip(bitset<200> x)
{
  int msb = getMsb(x);
  for (int i = msb; i >= 0; i--)
    x[i].flip();
  return x;
}
struct Node
{
  int d; bitset<200> u;
  int delta, msb;
  Node(int d, bitset<200> u) : d(d), u(u)
  {
    delta = min((u ^ emask).count(), (flip(u) ^ emask).count());
    msb = getMsb(u);
  }
  bool operator<(const Node &other) const { return d + delta > other.d + delta; }
  void print()
  {
    printf("%2d - %2d - ", d, delta);
    for (int i = 0; i < 10; i++) printf("%d", u[i] != 0);
    printf("\n");
  }
};
int dijkstra()
{
  priority_queue<Node> pq;
  pq.push(Node(0, smask));
  visited.clear();
  startTime = clock();
  while (!pq.empty())
  {
    // if (clock() - startTime > 1000000) return 1e9;
    Node now = pq.top(); pq.pop();
    DEBUG now.print();
    if (now.u == emask)
      return now.d;
    if (visited.count(now.u)) continue;
    visited.insert(now.u);

    Node l = Node(now.d + 1, flip(now.u));
    if (l.delta < 25) pq.push(l);
    Node r = Node(now.d + 1, now.u << 1);
    if (r.delta < 25) pq.push(r);
  }
  return 1e9;
}

char ss[101];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", ss);
    string s = string(ss);
    scanf(" %s", ss);
    string e = string(ss);

    DEBUG printf("%s - %s\n", s.c_str(), e.c_str());

    smask = 0;
    for (int i = s.size() - 1, j = 0; i >= 0; i--, j++)
      if (s[i] == '1')
        smask[j] = 1;
    emask = 0;
    for (int i = e.size() - 1, j = 0; i >= 0; i--, j++)
      if (e[i] == '1')
        emask[j] = 1;

    stop = false;
    startTime = clock();
    int ans = dijkstra();
    if (ans == 1e9) printf("Case #%d: IMPOSSIBLE\n", tt);
    else printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}