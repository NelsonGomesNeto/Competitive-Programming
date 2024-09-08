#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, a, b, c;
char s[maxN][3];
int kind[maxN];
int r[3][maxN + 1];

map<pair<int, int>, int> memo[maxN], path[maxN];
bool solve(int i = 0, int aa = a, int bb = b, int cc = c)
{
  if (aa < 0 || bb < 0 || cc < 0) return false;
  if (i == n) return true;
  aa = min(aa, n - i), bb = min(bb, n - i), cc = min(cc, n - i);
  if (aa == n - i && bb == n - i && cc == n - i) return true;
  pair<int, int> u = kind[i] == 0 ? make_pair(aa, bb) : kind[i] == 1 ? make_pair(aa, cc) : make_pair(bb, cc);
  if (memo[i].count(u))
    return memo[i][u];

  bool ans = false;
  if (kind[i] == 0)
  {
    bool aaa = solve(i + 1, aa + 1, bb - 1, cc);
    bool bbb = !aaa ? solve(i + 1, aa - 1, bb + 1, cc) : false;
    path[i][u] = aaa >= bbb ? 0 : 1;
    ans = max(aaa, bbb);
  }
  else if (kind[i] == 1)
  {
    bool aaa = solve(i + 1, aa + 1, bb, cc - 1);
    bool ccc = !aaa ? solve(i + 1, aa - 1, bb, cc + 1) : false;
    path[i][u] = aaa >= ccc ? 0 : 2;
    ans = max(aaa, ccc);
  }
  else
  {
    bool bbb = solve(i + 1, aa, bb + 1, cc - 1);
    bool ccc = !bbb ? solve(i + 1, aa, bb - 1, cc + 1) : false;
    path[i][u] = bbb >= ccc ? 1 : 2;
    ans = max(bbb, ccc);
  }
  return memo[i][u] = ans;
}

int main()
{
  while (scanf("%d %d %d %d", &n, &a, &b, &c) != EOF)
  {
    a = min(a, maxN), b = min(b, maxN), c = min(c, maxN);
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", s[i]);
      kind[i] = !strcmp(s[i], "AB") ? 0 : !strcmp(s[i], "AC") ? 1 : 2;
      memo[i].clear(), path[i].clear();
    }
    r[0][n] = r[1][n] = r[2][n] = 0;
    for (int i = n - 1; i >= 0; i--)
      for (int j = 0; j < 3; j++)
        r[j][i] = r[j][i + 1] + (kind[i] == j);

    bool ans = solve();
    if (!ans) printf("No\n");
    else
    {
      printf("Yes\n");
      for (int i = 0, aa = a, bb = b, cc = c; i < n; i++)
      {
        aa = min(aa, n - i), bb = min(bb, n - i), cc = min(cc, n - i);
        pair<int, int> u = kind[i] == 0 ? make_pair(aa, bb) : kind[i] == 1 ? make_pair(aa, cc) : make_pair(bb, cc);
        if (kind[i] == 0)
        {
          if (path[i][u] == 0)
            aa++, bb--, printf("A\n");
          else
            aa--, bb++, printf("B\n");
        }
        else if (kind[i] == 1)
        {
          if (path[i][u] == 0)
            aa++, cc--, printf("A\n");
          else
            aa--, cc++, printf("C\n");
        }
        else
        {
          if (path[i][u] == 1)
            bb++, cc--, printf("B\n");
          else
            bb--, cc++, printf("C\n");
        }
      }
    }
  }
  return 0;
}
