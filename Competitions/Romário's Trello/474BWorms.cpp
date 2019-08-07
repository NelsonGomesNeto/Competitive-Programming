#include <bits/stdc++.h>

int binsearch(int array[], int lo, int hi, int target)
{
  int mid = (lo + hi) / 2;
  if (lo >= hi) return(array[hi] == target ? hi : lo);
  if (target < array[mid]) return(binsearch(array, lo, mid - 1, target));
  else return(binsearch(array, mid, hi, target));
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
  }

  int queries, q; scanf("%d", &queries);
  while (queries -- > 0)
  {
    scanf("%d", &q);
    printf("%d\n", binsearch(worms, 0, at, q));
  }

  return(0);
}