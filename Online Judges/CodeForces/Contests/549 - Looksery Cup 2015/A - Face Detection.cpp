#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, m;
char wanted[5] = "face";
char s[maxN][maxN + 1];

int di[4] = {0, 0, 1, 1}, dj[4] = {1, 0, 1, 0};
bool has(int i, int j, char letter)
{
  for (int k = 0; k < 4; k ++)
    if (s[i + di[k]][j + dj[k]] == letter)
      return true;
  return false;
}
int valid(int i, int j)
{
  for (int k = 0; k < 4; k ++)
    if (!has(i, j, wanted[k]))
      return false;
  return true;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf(" %s", s[i]);

    int ans = 0;
    for (int i = 0; i < n - 1; i ++)
      for (int j = 0; j < m - 1; j ++)
        ans += valid(i, j);
    printf("%d\n", ans);
  }
  return 0;
}