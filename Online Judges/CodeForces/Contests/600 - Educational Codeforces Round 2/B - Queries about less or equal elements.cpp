#include <bits/stdc++.h>
using namespace std;

int bsupper(int a[], int lo, int hi, int target)
{
  int mid = (lo + hi) / 2;
  if (lo >= hi - 1) return(a[hi] <= target ? hi : a[lo] <= target ? lo : -1);
  if (target < a[mid])
    return(bsupper(a, lo, mid - 1 , target));
  else
    return(bsupper(a, mid, hi, target));
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int a[n], b[m];
  for (int i = 0; i < n; i ++)
    scanf("%d", &a[i]);
  for (int i = 0; i < m; i ++)
    scanf("%d", &b[i]);

  sort(a, a+n);

  for (int i = 0; i < m; i ++)
    printf("%d%c", bsupper(a, 0, n - 1, b[i]) + 1, i < m - 1 ? ' ' : '\n');

  return(0);
}