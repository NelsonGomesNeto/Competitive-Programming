#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3; int n;
lli mat[maxN][maxN], a[maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      scanf("%lld", &mat[i][j]);

  lli ab = mat[0][1], ac = mat[0][2], bc = mat[1][2];
  a[0] = sqrt(ab * ac / bc);
  for (int i = 1; i < n; i ++) a[i] = mat[0][i] / a[0];

  for (int i = 0; i < n; i ++)
    printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');

  return(0);
}
