#include <bits/stdc++.h>
using namespace std;

int lowerBound(int array[], int lo, int hi, int target)
{
  if (lo >= hi) return(array[lo] >= target ? lo : lo + 1);
  int mid = (lo + hi) / 2;
  if (target <= array[mid]) return(lowerBound(array, lo, mid, target));
  else return(lowerBound(array, mid + 1, hi, target));
}

int main()
{
  int n, l;
  while (scanf("%d %d", &n, &l) && !(!n && !l))
  {
    int spaces[l];
    for (int i = 0; i < l; i ++)
      scanf("%d", &spaces[i]);

    int minMoves = 1<<20;
    for (int i = 0; i < l; i ++)
      minMoves = min(minMoves, n - (lowerBound(spaces, 0, l - 1, spaces[i] + n) - i));
    printf("%d\n", minMoves);
  }
  return(0);
}