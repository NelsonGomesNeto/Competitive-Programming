#include <bits/stdc++.h>
using namespace std;
int field[500][500], pi, pj;

int lowerBound(int arr[], int lo, int hi, int target)
{
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    if (target <= arr[mid]) hi = mid;
    else lo = mid + 1;
  }
  return(lo);
  if (lo >= hi) return(lo);
  int mid = (lo + hi) >> 1;
  if (target <= arr[mid]) return(lowerBound(arr, lo, mid, target));
  return(lowerBound(arr, mid + 1, hi, target));
}

int upperBound(int lo, int hi, int target)
{
  while (lo < hi)
  {
    int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
    if (target < field[pi + mid][pj + mid]) hi = mid - 1;
    else lo = mid;
  }
  return(lo);
  if (lo >= hi) return(lo);
  int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  if (target < field[pi + mid][pj + mid]) return(upperBound(lo, mid - 1, target));
  return(upperBound(mid, hi, target));
}

int main()
{
  int n, m;
  while (scanf("%d %d", &n, &m) && !(!n && !m))
  {
    for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) scanf("%d", &field[i][j]);

    int q, lo, hi; scanf("%d", &q);
    while (q --)
    {
      scanf("%d %d", &lo, &hi);
      int biggest = 0;
      for (int i = 0; i < n; i ++)
      {
        int sj = lowerBound(field[i], 0, m - 1, lo);
        pi = i, pj = sj;
        // printf("--%d -- %d\n", sj, min(n - pi, m - pj) - 1);
        int diag = upperBound(0, min(n - pi, m - pj) - 1, hi);
        if (field[pi][pj] < lo || field[pi + diag][pj + diag] > hi) diag = -1;
        biggest = max(biggest, diag + 1);
      }
      printf("%d\n", biggest);
    }
    printf("-\n");
  }
  return(0);
}
