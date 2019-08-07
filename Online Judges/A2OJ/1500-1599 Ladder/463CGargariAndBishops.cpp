#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 2e3; int n;
lli table[maxN][maxN];
lli downLeft[2*maxN], downRight[2*maxN];
struct Position { int i, j; lli sum; };
Position white = {0, 0, -1}, black = {0, 0, -1};

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      scanf("%lld", &table[i][j]);

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      downLeft[i + j] += table[i][j], downRight[i - j + n - 1] += table[i][j];

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      lli sum = downLeft[i + j] + downRight[i - j + n - 1] - table[i][j];
      if (((i + j) & 1) && sum > white.sum) white.i = i, white.j = j, white.sum = sum;
      else if (!((i + j) & 1) && sum > black.sum) black.i = i, black.j = j, black.sum = sum;
    }

  printf("%lld\n%d %d %d %d\n", white.sum + black.sum, white.i + 1, white.j + 1, black.i + 1, black.j + 1);

  return(0);
}