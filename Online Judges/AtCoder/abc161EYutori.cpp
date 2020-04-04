#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5 + 10; int n, k, c;
char s[maxN + 1];

int memo[maxN + 1], options[2][maxN];
int acc[maxN + 1];
int solve(int i = 0)
{
  if (i >= n) return 0;
  if (memo[i] != -1) return memo[i];

  int ans = 0;
  if (s[i] == 'x') ans = max(ans, solve(i + 1));
  else
  {
    int working = 1 + solve(i + c + 1), notWorking = solve(i + 1);
    ans = max({ans, working, notWorking});
    options[0][i] = working, options[1][i] = notWorking;
  }
  return memo[i] = ans;
}

int main()
{
  int t = 0;
  while (scanf("%d %d %d", &n, &k, &c) != EOF)
  {
    if (t++) printf("---------\n");

    scanf(" %s", s);
    memset(memo, -1, sizeof(memo));
    solve();
    for (int i = n - 2; i >= 0; i--)
      memo[i] = max(memo[i], memo[i + 1]);
    for (int i = 0, cc = 0; i < n; i++)
    {
      acc[i + 1] = acc[i] + (s[i] == 'o' && i >= cc);
      if (s[i] == 'o' && i >= cc)
        cc = i + c + 1;
    }
    DEBUG
      for (int i = 0; i < n; i++)
        printf("%d%c", acc[i], i < n - 1 ? ' ' : '\n');

    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
      if (s[i] == 'x') continue;
      DEBUG printf("\t%d %d %d %d\n", i + 1, k, options[0][i], options[1][i]);
      int total = memo[0];
      DEBUG printf("\t\t%d %d %d %d\n", total, memo[i], memo[i + 1], acc[i]);
      if (acc[i] + options[1][i] < k)
        ans.push_back(i);
    }
    for (int i: ans)
      printf("%d\n", i + 1);
  }
  return 0;
}
// ooxxoxoxxxoxoxxo
//       ^