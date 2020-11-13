#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n;
const int inf = 1e6 + 1;
int w[maxN], b[maxN];
bitset<100> wmasks[maxN], bmasks[maxN];

// template <typename General>
// struct hash_function {
//   size_t operator()(General const& c) const {
//     size_t hashValue = 0;
//     for (int i = 0; i < n; i++)
//       hashValue += c[i] ? 1LL << min(i, n - i) : 0;
//     return(hashValue);
//   }
// };
unordered_set<bitset<100>> visited;
// unordered_map<bitset<100>, bool> bestWhite;

// map<bitset<100>, int> memo;
// map<bitset<100>, bool> bestWhite;
string res;

bitset<100> applyWhite(bitset<100> &from)
{
  bitset<100> after = 0;
  for (int i = 0; i < n; i++)
    if (from[i])
      after[w[i]] = after[w[i]] | true;
  return after;
}
bitset<100> applyBlack(bitset<100> &from)
{
  bitset<100> after = 0;
  for (int i = 0; i < n; i++)
    if (from[i])
      after[b[i]] = after[b[i]] | true;
  return after;
}

int it = 0;
// int solve(bitset<100> now, int i = 0)
// {
//   // printf("%d %d\n", i, now.count());
//   // DEBUG {
//   //   printf("%d\n", i);
//   //   for (int j: now) printf("%d ", j + 1);
//   //   printf("\n");
//   // }
//   if (it++ >= 4e4) return inf;

//   if (now.count() == 1) return 0;
//   if (memo.count(now)) return memo[now];
//   memo[now] = inf;

//   // white spell
//   int white = 1 + solve(applyWhite(now), i + 1);
//   if (white < inf)
//   {
//     bestWhite[now] = true;
//     return white;
//   }

//   // black spell
//   int black = 1 + solve(applyBlack(now), i + 1);

//   bestWhite[now] = false;
//   // if (white < black) bestWhite[now] = true;
//   // else bestWhite[now] = false;

//   return memo[now] = black;
// }

struct hehe
{
  int cnt, turns; string ans; bitset<100> now;
  bool operator<(const hehe &other) const { return cnt > other.cnt || (cnt == other.cnt && turns > other.turns); }
};
double mean = n;
string solve2(bitset<100> origin)
{
  priority_queue<hehe> pq;
  pq.push({n, 0, "", origin});
  while (!pq.empty())
  {
    auto u = pq.top(); pq.pop();
    if (u.cnt == 1) return u.ans;
    if (it++ > 4.9e4) return "impossible";
    if (visited.count(u.now)) continue;
    visited.insert(u.now);

    if (u.turns + 1 <= 2000)
    {
      auto white = applyWhite(u.now);
      pq.push({(int)white.count(), u.turns + 1, u.ans + "W", white});
      auto black = applyBlack(u.now);
      pq.push({(int)black.count(), u.turns + 1, u.ans + "B", black});
    }
  }
  return "impossible";
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &w[i]); w[i]--;
      wmasks[i] = 0;
      wmasks[i].set(w[i]);
    }
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &b[i]); b[i]--;
      bmasks[i] = 0;
      bmasks[i].set(b[i]);
    }

    bitset<100> now = 0;
    for (int i = 0; i < n; i++) now.set(i);
    visited.clear();
    it = 0;
    mean = n;
    res = solve2(now);
    // int ans = solve2(now);
    // if (ans >= inf) res = "impossible";
    // else
    // {
    //   res.clear();
    //   while (now.count() > 1)
    //   {
    //     if (bestWhite[now]) now = applyWhite(now), res += "W";
    //     else now = applyBlack(now), res += "B";
    //   }
    // }

    printf("%s\n", res.c_str());
  }
  return 0;
}