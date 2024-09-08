#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, k;
const int inf = 2*maxN;
char curr[maxN][7 + 1];

char digits[10][7 + 1] = {
  "1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"
};

int getDiff(char s[], char t[])
{
  int diff = 0;
  for (int i = 0; i < 7; i++)
  {
    diff += s[i] == '1' && t[i] == '0';
    if (s[i] == '0' && t[i] == '1')
      diff = inf;
  }
  return diff;
}

int memo[maxN][maxN], path[maxN][maxN];
bool solve(int i = 0, int kk = k)
{
  if (kk < 0) return false;
  if (i == n) return kk == 0;
  if (memo[i][kk] != -1) return memo[i][kk];

  bool ans = false;
  for (int d = 9; d >= 0; d--)
  {
    int diff = getDiff(digits[d], curr[i]);
    ans = max(ans, solve(i + 1, kk - diff));
    if (ans)
    {
      path[i][kk] = d;
      break;
    }
  }
  return memo[i][kk] = ans;
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", curr[i]);

    memset(memo, -1, sizeof(memo));
    bool ans = solve();
    if (!ans) printf("-1\n");
    else
    {
      string res = "";
      for (int i = 0, kk = k; i < n; i++)
      {
        res += '0' + path[i][kk];
        kk -= getDiff(digits[path[i][kk]], curr[i]);
      }
      printf("%s\n", res.c_str());
    }
  }
  return 0;
}
