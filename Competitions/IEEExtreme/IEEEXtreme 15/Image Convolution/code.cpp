#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e2; int n, m, r, c;
char s[maxN][maxN + 1];
char p[maxN][maxN + 1];
int accs[maxN + 1][maxN + 1], accp[maxN + 1][maxN + 1], acch[maxN + 1][maxN + 1];
int getSum(int acc[maxN + 1][maxN + 1], int loi, int loj, int hii, int hij)
{
  return acc[hii + 1][hij + 1] - acc[hii + 1][loj] - acc[loi][hij + 1] + acc[loi][loj];
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
      scanf(" %s", s[i]);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        accs[i + 1][j + 1] = accs[i + 1][j] + accs[i][j + 1] - accs[i][j] + (s[i][j] == '#');

    scanf("%d %d", &r, &c);
    for (int i = 0; i < r; i++)
      scanf(" %s", p[i]);
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
      {
        accp[i + 1][j + 1] = accp[i + 1][j] + accp[i][j + 1] - accp[i][j] + (p[i][j] == '#');
        acch[i + 1][j + 1] = acch[i + 1][j] + acch[i][j + 1] - acch[i][j] + (p[i][j] == '?');
      }

    int ans = 0;
    for (int i = 0; i + r - 1 < n; i++)
      for (int j = 0; j + c - 1 < m; j++)
      {
        bool valid = true;
        int required = getSum(accs, i, j, i + r - 1, j + c - 1);
        int got = getSum(accp, 0, 0, r - 1, c - 1);
        int wilds = getSum(acch, 0, 0, r - 1, c - 1);

        if (abs(required - got) > wilds)
          valid = false;

        for (int jj = 0; jj < c && valid; jj++)
        {
          required = getSum(accs, i, j + jj, i + r - 1, j + jj);
          got = getSum(accp, 0, jj, r - 1, jj);
          wilds = getSum(acch, 0, jj, r - 1, jj);

          if (abs(required - got) > wilds)
            valid = false;
        }

        for (int ii = 0; ii < r && valid; ii++)
        {
          required = getSum(accs, i + ii, j, i + ii, j + c - 1);
          got = getSum(accp, ii, 0, ii, c - 1);
          wilds = getSum(acch, ii, 0, ii, c - 1);

          if (abs(required - got) > wilds)
            valid = false;

          for (int jj = 0; jj < c && valid; jj++)
            if (p[ii][jj] != '?' && s[i + ii][j + jj] != p[ii][jj])
              valid = false;
        }
        ans += valid;
      }
    printf("%d\n", ans);
  }
  return 0;
}