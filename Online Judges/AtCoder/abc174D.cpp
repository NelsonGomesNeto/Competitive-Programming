#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const int inf = 1e6;
char c[maxN + 1];

// unordered_map<int, int> memo[maxN];
int memo[maxN][2];
int solve(int i = 0, int whites = 0, bool valid = true)
{
  if (i == n) return valid ? 0 : inf;
  if (memo[i][whites > 0] != -1) return memo[i][whites > 0];
  // if (memo[i].count(whites)) memo[i][whites];

  int ans = 0;
  if (c[i] == 'R' && whites)
  {
    ans = min(whites + solve(i + 1, 0, valid),
              1 + solve(i + 1, whites + 1, valid));
  }
  else
  {
    if (c[i] == 'R')
      ans = solve(i + 1, whites, valid);
    else
      ans = solve(i + 1, whites + 1, valid);
  }
  return memo[i][whites > 0] = ans;
  // return memo[i][whites] = ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    // for (int i = 0; i < n; i++) memo[i].clear();
    memset(memo, -1, sizeof(memo));

    scanf(" %s", c);
    int ans = inf;

    int w = 0, r = 0;
    for (int i = 0; i < n; i++)
      if (c[i] == 'W') w++;
      else r++;

    int redToLeft = r;
    for (int i = 0; i < r; i++)
      redToLeft -= c[i] == 'R';
    int whiteToRight = w;
    for (int i = n - 1, j = 0; j < w; i--, j++)
      whiteToRight -= c[i] == 'W';
    ans = min({ans, redToLeft, whiteToRight});

    printf("%d\n", ans);
  }
  return 0;
}
// WRWWRWRR
// RRRRWWWW
// 