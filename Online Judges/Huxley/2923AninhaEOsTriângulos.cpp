#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n, m;
int mat[maxN][maxN];

int area(int i, int j, int base)
{
  int cnt = 0; bool valid = true;
  // printf("%d %d %d - ", i, j, base);
  while (base > 0)
  {
    if (i < 0 || j + base - 1 >= m) { valid = false; break; }
    for (int k = 0; k < base; k ++, cnt ++)
      if (!mat[i][j + k])
        valid = false;
    base -= 2, i --, j ++;
  }
  // printf("%d %d\n", valid, cnt);
  return valid ? cnt : 0;
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      scanf("%d", &mat[i][j]);

  int ans = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      for (int base = 3; base <= m; base += 2)
      {
        int a = area(i, j, base);
        if (a) ans = max(ans, a);
      }
  printf("%d\n", ans);

  return(0);
}