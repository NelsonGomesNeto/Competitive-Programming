#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const int maxOp = 10;
char s[maxN + 1];

// map<pair<int, int>, int> memo[maxN], path[maxN];
int memo[maxOp][maxOp][maxN], path[maxOp][maxOp][maxN];
int solve(int i = 0, int oa = 0, int ob = 0)
{
  if (oa < 0 || ob < 0) return 0;
  int rem = n - i;
  if (oa > rem || ob > rem) return 0;
  if (oa >= maxOp || ob >= maxOp) return 0;
  if (i == n) return oa == 0 && ob == 0;

  // pair<int, int> curr = {oa, ob};
  // pair<int, int> curr = {oa, ob};
  // if (memo[i].count(curr)) return memo[i][curr];
  int &ans = memo[oa][ob][i];

  if (ans != -1)
    return ans;

  if (s[i] == '1')
  {
    int op = solve(i + 1, oa + 1, ob + 1), cl = solve(i + 1, oa - 1, ob - 1);
    path[oa][ob][i] = op > cl;
    ans = max(op, cl);
  }
  else
  {
    int op = solve(i + 1, oa + 1, ob - 1), cl = solve(i + 1, oa - 1, ob + 1);
    path[oa][ob][i] = op > cl;
    ans = max(op, cl);
  }
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %s", &n, s);

    // for (int i = 0; i < n; i++)
    //   memo[i].clear(), path[i].clear();
    for (int k = 0; k < maxOp; k++)
      for (int j = 0; j < maxOp; j++)
        for (int i = 0; i < n; i++)
          memo[k][j][i] = -1;
    bool can = solve();

    printf("%s\n", can ? "YES" : "NO");
    if (can)
    {
      string a, b;
      for (int i = 0, oa = 0, ob = 0; i < n; i++)
      {
        // pair<int, int> curr = {oa, ob};
        pair<int, int> curr = {oa, ob};
        if (s[i] == '1')
        {
          if (path[oa][ob][i])
            a += '(', b += '(', oa++, ob++;
          else
            a += ')', b += ')', oa--, ob--;
        }
        else
        {
          if (path[oa][ob][i])
            a += '(', b += ')', oa++, ob--;
          else
            a += ')', b += '(', oa--, ob++;
        }
      }
      printf("%s\n%s\n", a.c_str(), b.c_str());
    }
  }
  return 0;
}
