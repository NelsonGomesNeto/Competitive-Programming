#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n;
int a[maxN];

int ans;
int check2(int i, int bit)
{
  int xorsum = a[i], andsum = a[i];
  int j = i;
  while (j + 1 < n && (a[j + 1] & (1 << bit)))
  {
    xorsum ^= a[j + 1];
    andsum &= a[j + 1];
    if (andsum > xorsum) ans = max(ans, j - i + 2);
    j++;
  }
  DEBUG printf("\t%d %d:%d - %d %d\n", bit, i, j, xorsum, andsum);
  return j;
}
void check()
{
  for (int bit = 0; bit < 21; bit++)
  {
    for (int i = 0; i < n; i++)
    {
      if (a[i] & (1 << bit))
      {
        for (int k = 1; i + k < n && k < 4; k++) check2(i + k, bit);
        i = check2(i, bit);
      }
    }
  }
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    ans = 0;
    check();
    reverse(a, a+n);
    check();
    printf("%d\n", ans);
  }
  return 0;
}
