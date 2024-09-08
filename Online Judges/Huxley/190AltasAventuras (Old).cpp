#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n, k;

const int maxN = 1e3, maxK = 30;
int memo[maxN][maxK + 1], path[maxN][maxK + 1];
int solve(int options = n, int balloons = k)
{
  int& ans = memo[options][balloons];
  if (ans != -1) return ans;
  if (balloons == 1) return ans = options;
  if (options <= 1) return ans = options;
  int& chosen = path[options][balloons];

  ans = 1e9;
  for (int i = 1; i <= options; ++i)
  {
    int popping = i == 1 ? -1 : solve(i - 1, balloons - 1);
    int notPopping = solve(options - i, balloons);
    int worstCase = max(popping, notPopping) + 1;
    if (worstCase < ans)
      ans = worstCase, chosen = i;
  }
  DEBUG printf("\t%d %d = %d\n", options, balloons, ans);

  return ans;
}

map<int, int> memo2[maxK + 1];
int solve2(int options, int balloons);
int heuristicEval(int options, int balloons)
{
  int tests = balloons;
  while (tests-- && options > 1)
    options >>= 1;

  return (balloons - tests) - 2 + options + (options == 1);
}
int hEval(int i, int options, int balloons)
{
  if (options < maxN && balloons <= maxK) return solve(options, balloons);
  int popping = i == 1 ? -1 : heuristicEval(i - 1, balloons - 1);
  int notPopping = heuristicEval(options - i, balloons);
  int worstCase = max(popping, notPopping) + 1;
  return worstCase;
}
int eval(int i, int options, int balloons)
{
  if (options < maxN && balloons <= maxK) return solve(options, balloons);
  int popping = i == 1 ? -1 : solve2(i - 1, balloons - 1);
  int notPopping = solve2(options - i, balloons);
  int worstCase = max(popping, notPopping) + 1;
  return worstCase;
}
int it = 0;
int solve2(int options = n, int balloons = k)
{
  // if (++it % 1000000 == 0) printf("it: %d | %d %d\n", it, options, balloons);
  if (memo2[balloons].count(options)) return memo2[balloons][options];
  int& ans = memo2[balloons][options];
  if (balloons == 1) return ans = options;
  if (options <= 1) return ans = options;

  int lo = 1, hi = options;
  while (hi - lo >= 3)
  {
    int midlo = (2* lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
    int elo = hEval(midlo, options, balloons), ehi = hEval(midhi, options, balloons);
    if (elo < ehi) hi = midhi;
    else lo = midlo;
  }
  ans = 1e9;
  int bestI = -1;
  for (int i = lo; i <= hi; ++i)
  {
    int res = hEval(i, options, balloons);
    if (res < ans)
      bestI = i, ans = res;
  }
  ans = eval(bestI, options, balloons);

  return ans;
}

void printPath(int options = n, int balloons = k, string scenario = "", int depth = 0)
{
  int i = path[options][balloons], ans = memo[options][balloons];
  for (int k = 0; k < depth; ++k) printf("\t");
  printf("\t(%d, %d) = %d | %s | %d\n", options, balloons, ans, scenario.c_str(), i);
  if (balloons == 1) return;
  if (options <= 1) return;

  if (i != 1) printPath(i - 1, balloons - 1, scenario + "P", depth + 1);
  printPath(options - i, balloons, scenario + "O", depth + 1);
}

int main()
{
  memset(memo, -1, sizeof(memo));
  memset(path, -1, sizeof(path));
  while (~scanf("%d %d", &n, &k))
  {
    k = min(k, maxK);
    // int ans;

    // int tests = k - 1;
    // while (tests-- && n > 1)
    //   n >>= 1;

    // // ans = (k - tests) - 2 + n + (n == 1);
    // ans = (k - tests) + n;

    printf("%d | %d\n", n < maxN ? solve() : -1, solve2());
    // printPath();
  }
  return 0;
}
