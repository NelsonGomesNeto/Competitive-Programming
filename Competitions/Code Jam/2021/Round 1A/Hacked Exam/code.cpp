#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

__int128 gcd(__int128 a, __int128 b)
{
  return b == 0 ? gcd(b, a % b) : a;
}
__int128 lcm(__int128 a, __int128 b)
{
  return a / gcd(a, b) * b;
}
__int128 read()
{
  __int128 x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9')
  {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
  {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
void print(__int128 x)
{
  if (x < 0)
  {
    putchar('-');
    x = -x;
  }
  if (x > 9) print(x / 10);
  putchar(x % 10 + '0');
}
bool cmp(__int128 x, __int128 y) { return x > y; }
__int128 bigabs(__int128 x) { return x < 0 ? -x : x; }

const int maxN = 3, maxQ = 40; int n, q;
__int128 inf;
__int128 memo[maxQ][maxQ + 1][maxQ + 1][maxQ + 1];
char answers[maxN][maxQ + 1]; int scores[maxN];

__int128 solve2(int i, int a, int b, int c)
{
  if (i == q)
    return a == 0 && b == 0 && c == 0 ? 1 : 0;

  __int128 tot = 0
    + solve2(i + 1, a - (answers[0][i] == 'F'), b - (n >= 2 && answers[1][i] == 'F'), c - (n == 3 && answers[2][i] == 'F'))
    + solve2(i + 1, a - (answers[0][i] == 'T'), b - (n >= 2 && answers[1][i] == 'T'), c - (n == 3 && answers[2][i] == 'T'));
  return tot;
}
pair<__int128, __int128> solve(int i = 0, int a = scores[0], int b = scores[1], int c = scores[2])
{
  if (i == q)
    return a == 0 && b == 0 && c == 0 ? make_pair((__int128)1, (__int128)1) : make_pair(-inf, -inf);

  /*
    count with how many possible answers are valid and has only correct ones
    assuming that i-th problem has answer F = cnt(f)
    assuming that i-th problem has answer T = cnt(T)

    If I pick T: it's T / (F + T)
  */

  __int128 cntF = solve2(i + 1, a - (answers[0][i] == 'F'), b - (n >= 2 && answers[1][i] == 'F'), c - (n == 3 && answers[2][i] == 'F'));
  __int128 cntT = solve2(i + 1, a - (answers[0][i] == 'T'), b - (n >= 2 && answers[1][i] == 'T'), c - (n == 3 && answers[2][i] == 'T'));
  // __int128 cntF = 1, cntT = 1;
  pair<__int128, __int128> ansF = solve(i + 1, a - (answers[0][i] == 'F'), b - (n >= 2 && answers[1][i] == 'F'), c - (n == 3 && answers[2][i] == 'F'));
  pair<__int128, __int128> ansT = solve(i + 1, a - (answers[0][i] == 'T'), b - (n >= 2 && answers[1][i] == 'T'), c - (n == 3 && answers[2][i] == 'T'));
  // printf("\t");
  // print(cntF); printf(" | ");
  // print(cntT); printf(" | ");
  // print(ansF.first); printf("/"); print(ansF.second); printf(" | ");
  // print(ansT.first); printf("/"); print(ansT.second);
  // printf("\n");

  if (ansF.second != -inf && cntF != -inf)
  {
    __int128 d = cntF + cntT;
    __int128 l = lcm(d, ansF.second);
    ansF = make_pair(ansF.first * (l / d) + cntF * (l / ansF.second), l);
  }
  if (ansT.second != -inf && cntT != -inf)
  {
    __int128 d = cntF + cntT;
    __int128 l = lcm(d, ansT.second);
    ansT = make_pair(ansT.first * (l / d) + cntT * (l / ansT.second), l);
  }

  if (!(ansF.second != -inf && cntF != -inf))
    return ansT;
  if (!(ansT.second != -inf && cntT != -inf))
    return ansF;

  return max(ansT, ansF);
}

int main()
{
  inf = ((__int128)1) << 124;

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < q; j++)
        for (int m = 0; m < q; m++)
          for (int k = 0; k < q; k++)
            memo[i][j][m][k] = -1;
    memset(scores, 0, sizeof(scores));
    for (int i = 0; i < n; i++)
      scanf(" %s %d", answers[i], &scores[i]);

    pair<__int128, __int128> ans = solve();
    if (scores[0] + scores[1] + scores[2] == q * n)
      ans.first = q;
    printf("Case #%d: ", tt);
    print(ans.first);
    printf("/");
    print(ans.second);
    printf("\n");
  }
  return 0;
}