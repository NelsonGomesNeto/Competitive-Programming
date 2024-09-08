#include <bits/stdc++.h>
#define DEBUG if(0)

int binSearch(int array[], int lo, int hi, int target)
{
  int mid = (lo + hi) / 2;
  if (lo >= hi - 1) return(array[hi] <= target ? hi : array[lo] <= target ? lo : -1);
  if (target < array[mid])
    return(binSearch(array, lo, mid - 1, target));
  else
    return(binSearch(array, mid, hi, target));
}

int main()
{
  int belts, orcs;
  while (scanf("%d %d", &belts, &orcs) != EOF)
  {
    int belt[belts], prize[belts];
    for (int i = 0; i < belts - 1; i ++) scanf("%d", &belt[i]);
    for (int i = 0; i < belts; i ++) scanf("%d", &prize[i]);

    int power[orcs];
    for (int i = 0; i < orcs; i ++) scanf("%d", &power[i]);

    for (int i = 0; i < orcs; i ++)
    {
      DEBUG printf("%d\n", binSearch(belt, 0, belts - 2, power[i]));
      printf("%d%c", prize[binSearch(belt, 0, belts - 2, power[i]) + 1], i < orcs - 1 ? ' ' : '\n');
    } DEBUG printf("\n");
  }

  return(0);
}