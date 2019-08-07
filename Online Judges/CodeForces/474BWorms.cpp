#include <bits/stdc++.h>

int bsearch(int array[], int lo, int hi, int target)
{
  int mid = (lo + hi) / 2;
  if (lo >= hi) return(array[hi] == target ? hi : hi - 1);
  if (target <= array[mid]) return(bsearch(array, lo, mid, target));
  else return(bsearch(array, mid + 1, hi, target));
}

int main()
{
  int n; scanf("%d",  &n);
  int worms[n], pile, at = 1;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &pile);
    worms[i] = at;
    at += pile;
  } worms[n ++] = at;

  int queries, q; scanf("%d", &queries);
  while (queries -- > 0)
  {
    scanf("%d", &q);
    printf("%d\n", bsearch(worms, 0, n - 1, q) + 1);
  }

  return(0);
}