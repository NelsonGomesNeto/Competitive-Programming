#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 15; int n, mid;
char table[maxN][maxN + 1];

int solve(int i = 0, int column = 0, int mainDiagonal = 0, int subDiagonal = 0)
{
  if (i == n) return 1;

  int ans = 0;
  for (int j = 0; j < n; j++)
    if (table[i][j] == '.' && !(column & (1 << j)) && !(mainDiagonal & (1 << (mid + i - j))) && !(subDiagonal & (1 << (i + j))))
      ans += solve(i + 1, column | (1 << j), mainDiagonal | (1 << (mid + i - j)), subDiagonal | (1 << (i + j)));
  return ans;
}

int main()
{
  int t = 1;
  while (scanf("%d", &n) && n)
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", table[i]);

    mid = n - 1;
    int ans = solve();
    printf("Case %d: %d\n", t++, ans);
  }
  return 0;
}