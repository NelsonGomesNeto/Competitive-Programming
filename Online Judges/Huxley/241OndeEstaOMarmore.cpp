#include <bits/stdc++.h>
using namespace std;

int binSearch(int a[], int lo, int hi, int target)
{
  if (lo >= hi) return(a[lo] == target ? lo : -1);
  int mid = (lo + hi) / 2;
  if (target <= a[mid]) return(binSearch(a, lo, mid, target));
  return(binSearch(a, mid + 1, hi, target));
}

int main()
{
  int n, q, r = 1;
  while (scanf("%d %d", &n, &q) && !(!n && !q))
  {
    int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
    sort(a, a+n);
    printf("CASE# %d:\n", r ++);
    for (int i = 0; i < q; i ++)
    {
      int query; scanf("%d", &query);
      int pos = binSearch(a, 0, n - 1, query);
      if (pos == -1) printf("%d not found\n", query);
      else printf("%d found at %d\n", query, pos + 1);
    }
  }
  return(0);
}