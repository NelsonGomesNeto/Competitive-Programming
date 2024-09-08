#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n, m;
char ss[maxN + 1];
string mat[maxN];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      mat[i] = string(ss);
    }

    for (int i = 0; i < n; ++i)
      for (int j = 1; j < m; ++j)
        if (mat[i][j - 1] == 'T' && mat[i][j] == 'T')
          mat[i][j - 1] = 'P', mat[i][j] = 'C';

    for (int i = 0; i < n; ++i)
      printf("%s\n", mat[i].c_str());
  }
  return 0;
}
