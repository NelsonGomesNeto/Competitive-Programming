#include <stdio.h>

int lowerBound(int array[], int lo, int hi, int target)
{
  if (lo >= hi) return(array[lo] >= target ? lo : lo + 1);
  int mid = (lo + hi) / 2;
  if (target <= array[mid]) return(lowerBound(array, lo, mid, target));
  else return(lowerBound(array, mid + 1, hi, target));
}

int min(int a, int b)
{
  return(a < b ? a : b);
}

int main()
{
  int size, n;
  while (scanf("%d %d", &size, &n) && !(!size && !n))
  {
    int closet[n], i;
    for (i = 0; i < n; i ++)
      scanf("%d", &closet[i]);

    int minMoves = 1<<20;
    for (i = 0; i < n; i ++)
      minMoves = min(minMoves, size - (lowerBound(closet, 0, n - 1, closet[i] + size) - i));
    printf("%d\n", minMoves);
  }

  return(0);
}