#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1001; int n, sqrtn;
int table[maxN][maxN];
bool has[maxN];

bool valid()
{
  for (int i = 0; i < n; i ++)
  {
    memset(has, false, sizeof(has));
    for (int j = 0; j < n; j ++)
      has[table[i][j] - 1] = true;
    if (*min_element(has, has+n) == false)
      return false;
  }
  for (int j = 0; j < n; j ++)
  {
    memset(has, false, sizeof(has));
    for (int i = 0; i < n; i ++)
      has[table[i][j] - 1] = true;
    if (*min_element(has, has+n) == false)
      return false;
  }
  for (int i = 0; i < n; i += sqrtn)
    for (int j = 0; j < n; j += sqrtn)
    {
      memset(has, false, sizeof(has));
      for (int ii = 0; ii < sqrtn; ii ++)
        for (int jj = 0; jj < sqrtn; jj ++)
          has[table[i + ii][j + jj] - 1] = true;
      if (*min_element(has, has+n) == false)
        return false;
    }
  return true;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    sqrtn = sqrt(n);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        scanf("%d", &table[i][j]);

    printf("%s\n", valid() ? "YES" : "NO");
  }
  return 0;
}