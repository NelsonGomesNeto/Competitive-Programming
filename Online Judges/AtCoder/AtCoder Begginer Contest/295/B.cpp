#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 20;
int n, m;
char ss[maxN + 1];
string mat[maxN], ans[maxN];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      mat[i] = string(ss);
      ans[i] = string(ss);
    }

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (mat[i][j] != '.' && mat[i][j] != '#')
        {
          ans[i][j] = '.';
          const int power = mat[i][j] - '0';
          for (int ni = max(0, i - power); ni <= i + power && ni < n; ++ni)
            for (int nj = max(0, j - power); nj <= j + power && nj < m; ++nj)
            {
              const int dist = abs(ni - i) + abs(nj - j);
              if (dist <= power)
                ans[ni][nj] = '.';
            }
        }

    for (int i = 0; i < n; ++i)
      printf("%s\n", ans[i].c_str());
  }
  return 0;
}
