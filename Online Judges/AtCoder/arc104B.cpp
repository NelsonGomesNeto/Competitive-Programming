#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n;
char s[maxN + 1];
char atcg[5] = "ATCG";
int charMap[255];
int acc[4][maxN];

int getSum(int a, int i, int j)
{
  return acc[a][j + 1] - acc[a][i];
}

int main()
{
  while (scanf("%d %s", &n, s) != EOF)
  {
    for (int i = 0; i < 5; i++) charMap[atcg[i]] = i;

    for (int a = 0; a < 4; a++)
      for (int i = 0; i < n; i++)
        acc[a][i + 1] = acc[a][i] + (s[i] == atcg[a]);

    int ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = i; j < n; j++)
        ans += getSum(0, i, j) == getSum(1, i, j) && getSum(2, i, j) == getSum(3, i, j);
    printf("%d\n", ans);
  }
  return 0;
}