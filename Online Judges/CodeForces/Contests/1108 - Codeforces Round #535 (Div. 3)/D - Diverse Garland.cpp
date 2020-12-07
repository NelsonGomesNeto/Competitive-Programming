#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
char s[maxN + 1], colors[4] = "RBG";
char fs[maxN + 1];
int memo[4][maxN], path[4][maxN], colorMap[256];

int solve(int i = 0, char prv = 'a')
{
  if (i == n) return(0);
  if (memo[colorMap[prv]][i] == -1)
  {
    int ans = 1e6; char now = s[i];
    for (int k = 0; k < 3; k ++)
    {
      if (colors[k] == prv) continue;
      int ret = solve(i + 1, colors[k]) + (now != colors[k]);
      if (ret < ans)
        ans = ret, s[i] = colors[k], path[colorMap[prv]][i] = k;
    }
    s[i] = now;
    memo[colorMap[prv]][i] = ans;
  }
  return(memo[colorMap[prv]][i]);
}

int main()
{
  colorMap['R'] = 0, colorMap['G'] = 1, colorMap['B'] = 2, colorMap['a'] = 3;
  scanf("%d\n%s", &n, s);
  memset(memo, -1, sizeof(memo));
  int ans = solve(), i = 0; char prv = 'a';
  for (; i < n; i ++)
  {
    fs[i] = colors[path[colorMap[prv]][i]];
    prv = fs[i];
  }
  printf("%d\n%s", ans, fs);
  return(0);
}