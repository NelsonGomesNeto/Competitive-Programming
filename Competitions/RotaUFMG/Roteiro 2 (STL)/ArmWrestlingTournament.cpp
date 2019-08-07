#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t -- > 0)
  {
    int n, k; scanf("%d %d", &n, &k);
    pair<int, int> str[(int) pow(2, n)][n + 2]; int p;
    int wonAgainst[(int) pow(2, n) + 1][n];
    for (int i = 0; i < pow(2, n); i ++)
    {
      scanf("%d", &p);
      str[i][0].first = p; str[i][0].second = i + 1;
    }

    for (int i = 0; i <= n; i ++)
    {
      DEBUG for (int j = 0; j < pow(2, n - i); j ++) printf("(%d,%d)%c", str[j][i].second, str[j][i].first, j < pow(2, n - i) - 1 ? ' ' : '\n');
      for (int j = 0; j < pow(2, n - i); j += 2)
      {
        if (str[j][i].first > str[j + 1][i].first || (str[j][i].first == str[j + 1][i].first && str[j][i].second < str[j + 1][i].second))
        {
          str[j / 2][i + 1].first = min(str[j][i].first - str[j + 1][i].first + k, str[str[j][i].second - 1][0].first);
          str[j / 2][i + 1].second = str[j][i].second;
          wonAgainst[str[j][i].second][i] = str[j + 1][i].second;
        }
        else
        {
          str[j / 2][i + 1].first = min(str[j + 1][i].first - str[j][i].first + k, str[str[j + 1][i].second - 1][0].first);
          str[j / 2][i + 1].second = str[j + 1][i].second;
          wonAgainst[str[j + 1][i].second][i] = str[j][i].second;
        }
      }
    }

    printf("%d\n", str[0][n].second);
    for (int i = 0; i < n; i ++)
      printf("%d%c", wonAgainst[str[0][n].second][i], i < n - 1 ? ' ' : '\n');
  }
  return(0);
}