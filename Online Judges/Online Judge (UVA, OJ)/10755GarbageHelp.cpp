#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;
lli mat[20][20][20], accRect[21][20][20], accCube[21][21][20], arr[20], a, b, c, inf = 1e18;

void printCube()
{
  for (int j = 0; j < b; j ++)
    for (int i = 0; i < a; i ++)
    {
      for (int k = 0; k < c; k ++)
        printf("%2lld", mat[i][j][k]);
      printf("%c", i < a - 1 ? ' ' : '\n');
    }
}

lli kadane()
{
  lli sum = 0, hasPositive = 0, biggest = -inf;
  for (int i = 0; i < c && !hasPositive; i ++) hasPositive = arr[i] >= 0, biggest = max(biggest, arr[i]);
  if (!hasPositive) return(biggest);
  for (int i = 0; i < c; i ++)
  {
    sum += arr[i];
    biggest = max(biggest, sum);
    if (sum < 0) sum = 0;
  }
  return(biggest);
}

int main()
{
  int t, r = 0; scanf("%d", &t);
  while (t --)
  {
    if (r ++) printf("\n");
    scanf("%lld %lld %lld", &a, &b, &c);
    lli totalSum = 0;
    for (int i = 0; i < a; i ++) for (int j = 0; j < b; j ++) for (int k = 0; k < c; k ++)
    {
      scanf("%lld", &mat[i][j][k]);
      totalSum += mat[i][j][k];
    }
    DEBUG printCube();

    memset(accRect, 0, sizeof(accRect)); memset(accCube, 0, sizeof(accCube));
    for (int i = 1; i <= a; i ++)
    {
      for (int j = 0; j < b; j ++)
        for (int k = 0; k < c; k ++)
        accRect[i][j][k] = accRect[i - 1][j][k] + mat[i - 1][j][k];
      for (int k = 0; k < c; k ++)
        for (int j = 1; j <= b; j ++)
          accCube[i][j][k] = accCube[i][j - 1][k] + accRect[i][j - 1][k];
    }

    lli ans = totalSum;
    // bruteforce depth
    for (int dlo = 0; dlo < a; dlo ++)
      for (int dhi = dlo; dhi < a; dhi ++)
        // choosing rows
        for (int rlo = 0; rlo < b; rlo ++)
          for (int rhi = rlo; rhi < b; rhi ++)
          {
            memset(arr, 0, sizeof(arr));
            // for (int i = rlo; i <= rhi; i ++) O(n^6)
            //   for (int j = 0; j < c; j ++)
            //     arr[j] += accRect[dhi + 1][i][j] - accRect[dlo][i][j];
            for (int j = 0; j < c; j ++) // O(n^5)
              arr[j] = (accCube[dhi + 1][rhi + 1][j] - accCube[dlo][rhi + 1][j]) - (accCube[dhi + 1][rlo][j] - accCube[dlo][rlo][j]);
            ans = max(ans, kadane());
          }
    printf("%lld\n", ans);
  }
  return(0);
}
