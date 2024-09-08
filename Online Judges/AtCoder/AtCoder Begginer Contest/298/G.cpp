#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = LONG_LONG_MAX;

const int maxN = 6;
int n, m, t;
lli s[maxN][maxN];
lli sumTable[maxN][maxN][maxN][maxN];

struct Piece
{
  int loi, loj, hii, hij;
  lli sum() const
  {
    return sumTable[loi][loj][hii][hij];
  }
  void print(string prefix) const
  {
    printf("%s(%d, %d) (%d %d)\n", prefix.c_str(), loi, loj, hii, hij);
  }
  const bool operator<(const Piece& other) const
  {
    return loi < other.loi
        || (loi == other.loi && loj < other.loj)
        || (loi == other.loi && loj == other.loj && hii < other.hii)
        || (loi == other.loi && loj == other.loj && hii == other.hii && hij < other.hij);
  }
};
lli eval(const set<Piece>& pieces)
{
  lli M = 0;
  lli m = inf;
  for (const auto &p : pieces)
  {
    DEBUG p.print("\t\t");
    M = max(M, p.sum());
    m = min(m, p.sum());
  }
  DEBUG printf("\t%lld %lld\n", M, m);
  return M - m;
}

map<set<Piece>, lli> memo;
lli upperBound;
lli solve(set<Piece> pieces = {{0, 0, n - 1, m - 1}})
{
  if (pieces.size() == t + 1)
  {
    lli e = eval(pieces);
    upperBound = min(upperBound, e);
    return e;
  }
  if (memo.count(pieces)) return memo[pieces];

  lli& ans = memo[pieces];
  ans = inf;
  for (const auto& p : pieces)
  {

    for (int i = p.loi + 1; i <= p.hii; ++i)
    {
      Piece pp = p;
      Piece np = p;
      np.loi = i;
      pp.hii = i - 1;
      set<Piece> hehe = pieces;
      hehe.erase(p);
      hehe.insert(pp);
      hehe.insert(np);
      ans = min(ans, solve(hehe));
    }
    for (int j = p.loj + 1; j <= p.hij; ++j)
    {
      Piece pp = p;
      Piece np = p;
      np.loj = j;
      pp.hij = j - 1;
      set<Piece> hehe = pieces;
      hehe.erase(p);
      hehe.insert(pp);
      hehe.insert(np);
      ans = min(ans, solve(hehe));
    }
  }

  return ans;
}

struct State
{
  set<Piece> pieces;
  lli value;
  bool operator<(const State& other) const
  {
    return value > other.value
        || (value == other.value && pieces.size() > other.pieces.size());
  }
};

lli dijkstra()
{
  set<Piece> startPieces = {{0, 0, n - 1, m - 1}};
  priority_queue<State> pq;
  pq.push(State{startPieces, eval(startPieces)});
  lli ans = inf;
  int trials = 0;
  while (!pq.empty())
  {
    State s = pq.top();
    pq.pop();
    if (memo.count(s.pieces)) continue;
    memo[s.pieces] = s.value;

    if (s.pieces.size() == t + 1)
    {
      ans = min(ans, s.value);
      if (++trials > 1e4) break;
      continue;
    }

    for (const auto &p : s.pieces)
    {
      for (int i = p.loi + 1; i <= p.hii; ++i)
      {
        Piece pp = p;
        Piece np = p;
        np.loi = i;
        pp.hii = i - 1;
        set<Piece> hehe = s.pieces;
        hehe.erase(p);
        hehe.insert(pp);
        hehe.insert(np);
        if (memo.count(hehe)) continue;
        pq.push(State{hehe, eval(hehe)});
      }
      for (int j = p.loj + 1; j <= p.hij; ++j)
      {
        Piece pp = p;
        Piece np = p;
        np.loj = j;
        pp.hij = j - 1;
        set<Piece> hehe = s.pieces;
        hehe.erase(p);
        hehe.insert(pp);
        hehe.insert(np);
        if (memo.count(hehe)) continue;
        pq.push(State{hehe, eval(hehe)});
      }
    }
  }
  return ans;
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &t))
  {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        scanf("%lld", &s[i][j]);

    for (int loi = 0; loi < n; ++loi)
      for (int hii = loi; hii < n; ++hii)
        for (int loj = 0; loj < m; ++loj)
          for (int hij = loj; hij < m; ++hij)
          {
            lli &ans = sumTable[loi][loj][hii][hij];
            ans = 0;
            for (int i = loi; i <= hii; ++i)
              for (int j = loj; j <= hij; ++j)
                ans += s[i][j];
          }

    memo.clear();
    upperBound = inf;
    lli ans = dijkstra();
    memo.clear();
    lli hehe = 3;
    printf("%lld %lld\n", ans, hehe);
  }
  return 0;
}
