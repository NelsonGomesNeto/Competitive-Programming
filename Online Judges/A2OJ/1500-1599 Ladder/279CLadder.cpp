#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, q;
int a[maxN];
int up[maxN], down[maxN];

int main()
{
  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);

  for (int i = n - 2; i >= 0; i --)
    if (a[i] <= a[i + 1])
      up[i] = up[i + 1] + 1;
  for (int i = 1; i < n; i ++)
    if (a[i] <= a[i - 1])
      down[i] = down[i - 1] + 1;

  for (int i = 0, lo, hi; i < q; i ++)
  {
    scanf("%d %d", &lo, &hi); lo --, hi --;
    // printf("%d %d - %d %d\n", lo, hi, up[lo], down[hi]);
    if (up[lo] + down[hi] + 1 >= hi - lo + 1) printf("Yes\n");
    else printf("No\n");
  }

  return(0);
}