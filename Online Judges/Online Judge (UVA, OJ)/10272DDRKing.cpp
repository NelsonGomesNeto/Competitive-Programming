#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  This problem is BROKEN
*/

const int maxN = 50, maxM = 1e7 + 1; int n, k, m;

unordered_map<int, bool> memo[maxN + 1][maxN + 1][2];
bool solve(int i = 0, int c = 0, bool done = false, int score = 0)
{
  DEBUG printf("%d %d %d %d\n", i, c, done, score);
  done |= c == k;
  if (score == m && done) return true;
  if (score > m || i == n) return false;
  if (memo[i][c][done].count(score)) return memo[i][c][done][score];

  if (c < k)
  {
    int v = ((c + 1) / 4)*((c + 1) / 4) + 1;
    if (solve(i + 1, c + 1, done, score + v * 3))
      return memo[i][c][done][score] = true;
    if (solve(i + 1, c + 1, done, score + v))
      return memo[i][c][done][score] = true;
  }
  return memo[i][c][done][score] = solve(i + 1, 0, done, score);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d", &n, &k, &m);
    if (m % 100 != 0 || k > n) printf("No\n");
    else
    {
      m /= 100;
      DEBUG printf("\t%d %d %d\n", n, k, m);

      lli minimum = 0, maximum = 0;
      for (int c = 1; c <= k; c++)
      {
        lli v = (c / 4) * (c / 4) + 1;
        minimum += v;
      }
      int maxPerfects = n;
      for (int i = 0, c = 0; i < n; i++)
      {
        c++;
        lli v = (c / 4) * (c / 4) + 1;
        maximum += 3*v;
        if (c == k) c = 0, i++, maxPerfects--;
      }

      if (n <= maxN)
      {
        for (int i = 0; i < n; i++)
          for (int j = 0; j <= k; j++)
            memo[i][j][0].clear(), memo[i][j][1].clear();
      }
      bool can = n <= maxN ? solve() : minimum <= m && maximum >= m;

      DEBUG printf("%d - %lld (%d) %lld (%d) %d (%d)\n", tt, minimum, minimum <= m, maximum, maximum >= m, m, can);
      printf("%s\n", can ? "Yes" : "No");
    }
  }
  return 0;
}