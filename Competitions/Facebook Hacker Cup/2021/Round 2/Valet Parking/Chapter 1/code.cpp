#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e6; int n, m, k;
char s[maxN + 1];
string mat[maxN];
vector<int> accD[maxN], accU[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d", &n, &m, &k); k--;
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", s);
      mat[i] = string(s);
    }

    for (int j = 0; j < m; j++)
    {
      accD[j].clear(); accD[j].resize(n + 1);
      accU[j].clear(); accU[j].resize(n + 1);

      accD[j][0] = 0;
      for (int i = 0; i < n; i++)
        accD[j][i + 1] = accD[j][i] + (mat[i][j] == 'X');
      
      accU[j][n] = 0;
      for (int i = n - 1; i >= 0; i--)
      {
        accU[j][i] = accU[j][i + 1] + (mat[i][j] == 'X');
      }
    }

    int ans = m;
    // move down
    for (int moves = 0; moves < n; moves++)
    {
      int cnt = 0, i = k - moves;
      int ii = max(0, i);
      for (int j = 0; j < m; j++)
      {
        cnt += (i >= 0 && mat[i][j] == 'X') || (accU[j][ii] >= n - k);
      }
      DEBUG printf("\tdown %d %d\n", cnt, moves);
      ans = min(ans, cnt + moves);
    }

    // move up
    for (int moves = 0; moves < n; moves++)
    {
      int cnt = 0, i = k + moves;
      int ii = min(i, n - 1);
      for (int j = 0; j < m; j++)
      {
        cnt += (i < n && mat[i][j] == 'X') || (accD[j][ii + 1] >= k + 1);
      }
      DEBUG printf("\tup %d %d\n", cnt, moves);
      ans = min(ans, cnt + moves);
    }
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}
