#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 40; int n, A, B;
char d[maxN + 1];
int digits[maxN];
int modPot[maxN + 1][maxN + 1];

int memo[maxN][maxN][maxN][maxN], path[maxN][maxN][maxN][maxN];
int solve(int i = 0, int r = 0, int b = 0, int rema = 0, int remb = 0)
{
  if (i == n) return !rema && !remb && r && b ? abs(r - b) : 1e5;
  int &ans = memo[i][r][rema][remb], &p = path[i][r][rema][remb];
  if (ans != -1) return ans;

  int rr = solve(i + 1, r + 1, b, (rema + modPot[A][r]*digits[i]) % A, remb);
  int bb = solve(i + 1, r, b + 1, rema, (remb + modPot[B][b]*digits[i]) % B);
  if (rr <= bb) ans = rr, p = 0;
  else ans = bb, p = 1;

  return ans;
}

int main()
{
  for (int i = 1; i <= maxN; i++)
  {
    int p = 1;
    for (int j = 0; j <= maxN; j++)
    {
      modPot[i][j] = p;
      p = p * 10 % i;
    }
  }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d", &n, &A, &B);
    scanf(" %s", d);
    for (int i = 0; i < n; i++) digits[i] = d[i] - '0';
    reverse(digits, digits+n);

    memset(memo, -1, sizeof(memo));
    memset(path, -1, sizeof(path));
    int ans = solve();
    DEBUG printf("\t%d\n", ans);

    if (ans >= 1e5) printf("-1\n");
    else
    {
      string res = "";
      for (int i = 0, r = 0, b = 0, rema = 0, remb = 0; i < n; i++)
      {
        if (path[i][r][rema][remb] == 0)
        {
          res += 'R';
          rema = (rema + modPot[A][r]*digits[i]) % A;
          r++;
        }
        else
        {
          res += 'B';
          remb = (remb + modPot[B][b]*digits[i]) % B;
          b++;
        }
      }
      reverse(res.begin(), res.end());
      printf("%s\n", res.c_str());
    }
  }
  return 0;
}
