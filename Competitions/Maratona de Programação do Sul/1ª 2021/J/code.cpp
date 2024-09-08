#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
char mat[maxN][maxN + 1];
vector<int> lines[maxN], columns[maxN];
vector<int> mainDiag[2*maxN - 1], subDiag[2*maxN - 1];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) scanf(" %s", mat[i]);

    for (int i = 0; i < n; i++)
    {
      lines[i].clear();
      for (int j = 0; j < n; j++)
        if (mat[i][j] == 'P')
          lines[i].push_back(j);
    }

    for (int j = 0; j < n; j++)
    {
      columns[j].clear();
      for (int i = 0; i < n; i++)
        if (mat[i][j] == 'P')
          columns[j].push_back(i);
    }

    for (int i = 0; i < 2*n; i++) mainDiag[i].clear(), subDiag[i].clear();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
        if (mat[i][j] == 'P')
          mainDiag[i + j].push_back(i);
        if (mat[i][j] == 'P')
          subDiag[i - j + n - 1].push_back(i);
      }

    int ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (mat[i][j] == '.')
        {
          int lineCnt = (!lines[i].empty() && lines[i].back() > j)
                      + (!lines[i].empty() && lines[i][0] < j);
          int columnCnt = (!columns[j].empty() && columns[j].back() > i)
                        + (!columns[j].empty() && columns[j][0] < i);

          int mainDiagCnt = (!mainDiag[i + j].empty() && mainDiag[i + j].back() > i)
                          + (!mainDiag[i + j].empty() && mainDiag[i + j][0] < i);

          int subDiagCnt = (!subDiag[i - j + (n - 1)].empty() && subDiag[i - j + (n - 1)].back() > i)
                         + (!subDiag[i - j + (n - 1)].empty() && subDiag[i - j + (n - 1)][0] < i);

          int sum = lineCnt + columnCnt + mainDiagCnt + subDiagCnt;
          ans = max(ans, sum);
        }

    printf("%d\n", ans);
  }
  return 0;
}