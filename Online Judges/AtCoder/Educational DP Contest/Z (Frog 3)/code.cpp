#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxX = 1e6 + 2; int n; lli c;
const lli inf = LONG_LONG_MAX;
lli h[maxN];

lli memo[maxN];
lli solve(int i = 0)
{
  if (i == n - 1) return 0;
  lli &ans = memo[i];
  if (ans != -1) return ans;

  ans = inf;
  for (int j = i + 1; j < n; j++)
    ans = min(ans, solve(j) + (h[i] - h[j])*(h[j] - h[i]) + c);
  return ans;
}

// y = m*x + b
struct Line
{
  lli m, b;
  lli value(lli x)
  {
    return m*x + b;
  }
};
struct LiChaoTree
{
  int size;
  vector<Line> lines;
  LiChaoTree() { }
  LiChaoTree(int sz) : size(sz)
  {
    Line nilLine = {0, inf};
    lines.resize(4*sz, nilLine);
  }
  void addLine(Line newLine) { addLine(newLine, 1, 0, size - 1); }
  void addLine(Line &newLine, int i, int lo, int hi)
  {
    int mid = (lo + hi) >> 1;
    bool leftEval = newLine.value(lo) < lines[i].value(lo);
    bool midEval = newLine.value(mid) < lines[i].value(mid);
    if (midEval) swap(newLine, lines[i]);

    if (lo == hi - 1) return;
    if (leftEval != midEval) addLine(newLine, 2*i, lo, mid);
    else addLine(newLine, 2*i + 1, mid, hi);
  }
  lli get(int x) { return get(x, 1, 0, size - 1); }
  lli get(int x, int i, int lo, int hi)
  {
    if (lo == hi - 1) return lines[i].value(x);
    int mid = (lo + hi) >> 1;
    if (x < mid) return min(lines[i].value(x), get(x, 2*i, lo, mid));
    else return min(lines[i].value(x), get(x, 2*i + 1, mid, hi));
  }
};
LiChaoTree liChaoTree;
// vector<Line> lines;
lli solve2()
{
  for (int i = 0; i < n; i++) memo[i] = inf;
  
  memo[0] = 0;
  liChaoTree = LiChaoTree(maxX);
  liChaoTree.addLine(Line{-2*h[0], h[0]*h[0] + memo[0]});
  // memo[1] = (h[1] - h[0])*(h[1] - h[0]) + c;
  // liChaoTree.addLine(Line{-2*h[1], h[1]*h[1] + memo[1]});

  // lines.push_back(Line{-2*h[0], h[0]*h[0] + memo[0]});
  for (int i = 1; i < n; i++)
  {
    // for (Line &line: lines)
    // {
    //   // lli toAdd = (h[i] - h[j])*(h[i] - h[j]);
    //   memo[i] = min(memo[i], line.value(h[i]));
    // }
    memo[i] = liChaoTree.get(h[i]);
    memo[i] += h[i]*h[i] + c;
    // lines.push_back(Line{-2*h[i], h[i]*h[i] + memo[i]});
    liChaoTree.addLine(Line{-2*h[i], h[i]*h[i] + memo[i]});
  }
  return memo[n - 1];
}

int main()
{
  while (scanf("%d %lld", &n, &c) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &h[i]);

    lli ans = solve2();
    printf("%lld\n", ans);
  }
  return 0;
}
