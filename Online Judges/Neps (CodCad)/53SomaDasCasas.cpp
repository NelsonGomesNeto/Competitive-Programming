#include <bits/stdc++.h>

int binSearch(int array[], int lo, int hi, int target)
{
  int mid = (lo + hi) / 2;
  if (lo >= hi) return(array[mid] == target ? mid : -1);
  if (target <= array[mid])
    return(binSearch(array, lo, mid, target));
  else
    return(binSearch(array, mid + 1, hi, target));
}

int main()
{
  int toys; scanf("%d", &toys);
  int house[toys];
  for (int i = 0; i < toys; i ++)
    scanf("%d", &house[i]);

  int sum; scanf("%d", &sum);

  for (int i = 0; i < toys; i ++)
    if (binSearch(house, 0, toys - 1, sum - house[i]) != -1)
    {
      printf("%d %d\n", house[i], sum - house[i]);
      return(0);
    }

  return(0);
}
