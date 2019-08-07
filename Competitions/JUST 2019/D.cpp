#include <bits/stdc++.h>
using namespace std;

void read(int a[])
{
  for (int i = 0; i < 10; i ++) scanf("%01d", &a[i]);
  // sort(a, a+10);
}

int countOnes(int a[])
{
  int ones = 0;
  for (int i = 0; i < 10; i ++) ones += a[i];
  return(ones);
}
int aa[3][2], b[2][3];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int a[3][10], d[10]; memset(d, 0, sizeof(d));
    read(a[0]); read(a[1]); read(a[2]);
    for (int i = 0; i < 3; i ++) { aa[i][0] = countOnes(a[i]); aa[i][1] = 10 - aa[i][0]; }

    for (int i = 0; i < 2; i ++)
    {
      b[i][0] = min(aa[i][0], aa[i + 1][0]) + min(aa[i][1], aa[i + 1][1]);
      b[i][1] = min(aa[i][0], aa[i + 1][1]) + min(aa[i][1], aa[i + 1][0]);
      b[i][2] = max(min(aa[i][0], aa[i + 1][1]), min(aa[i][1], aa[i + 1][0]));
    }
    b[1][1] = 0;
    for (int i = 0; i <= min(b[0][0], b[0][1]); i ++)
    {
      b[1][1] = max(b[1][1], 10 - min(b[0][0] - i, aa[2][1]) + min(10 - (b[0][0] - i), aa[2][0]));
    }

    int ans = b[1][1];
    for (int i = 0; i < ans; i ++) printf("1");
    for (int i = 0; i < 10 - ans; i ++) printf("0");
    printf("\n");
  }
  return(0);
}