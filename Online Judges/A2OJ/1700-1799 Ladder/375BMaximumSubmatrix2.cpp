#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  columnBlocks[j][i] = Amount of size (i + 1) blocks of ones at column j
  If we had that, we could just:
    ans = max((i + 1) * columnBlocks[j][i] for all i and j in [0, m - 1])

  We can build it as follows:
    for n in [0 : n - 1]
      total = 0
      for j in [0 : m - 1]
        if (mat[i][j] == 1)
          columnBlocks[j][total ++] ++
        else
          total = 0
    So you're always filling size 1 when it happens, and for the next
    column, if it happens to also have a 1: you'll fill for size 2.
    There will be gaps, but you just need to fill from right to left (i):
      columnBlocks[j][i] += columnBlocks[j][i + 1]
*/

const int maxN = 5000; int n, m;
int columnBlocks[maxN][maxN];
char s[maxN][maxN + 1];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    memset(columnBlocks, 0, sizeof(columnBlocks));
    for (int i = 0; i < n; i ++)
    {
      scanf(" %s", s[i]);
      for (int j = 0, total = 0; j < m; j ++)
        if (s[i][j] - '0')
          columnBlocks[j][total ++] ++;
        else
          total = 0;
    }

    for (int j = 0; j < m; j ++)
      for (int i = m - 2; i >= 0; i --)
        columnBlocks[j][i] += columnBlocks[j][i + 1];

    DEBUG {
      for (int j = 0; j < m; j ++)
        for (int i = 0; i < m; i ++)
          printf("%d%c", columnBlocks[j][i], i < m - 1 ? ' ' : '\n');
      printf("---------\n");
    }

    int ans = 0;
    for (int j = 0; j < m; j ++)
      for (int i = 0; i < m && columnBlocks[j][i]; i ++)
        ans = max(ans, (i + 1) * columnBlocks[j][i]);
    printf("%d\n", ans);
  }

  return 0;
}