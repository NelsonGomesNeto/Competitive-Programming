#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int

void printArray(int array[], int lo, int hi)
{
  printf("%d %d %d: ", lo, (lo + hi) / 2, hi);
  for (int i = lo; i <= hi; i ++)
    printf("%d%c", array[i], i < hi ? ' ' : '\n');
}

lli merge(int array[], int lo, int mid, int hi)
{
  int copy[hi - lo + 1], i = lo, j = mid + 1, at = 0; lli inversions = 0;
  while (i <= mid || j <= hi)
  {
    if (i == mid + 1) copy[at ++] = array[j ++];
    else if (j == hi + 1) copy[at ++] = array[i ++];
    else if (array[i] > array[j])
    {
      copy[at ++] = array[j ++]; inversions += (mid - i + 1);
    }
    else copy[at ++] = array[i ++];
  }
  for (i = 0; i <= (hi - lo); i ++)
    array[lo + i] = copy[i];
  DEBUG printf("%lld - ", inversions);
  DEBUG printArray(array, lo, hi);
  return(inversions);
}

lli mergeSort(int array[], int lo, int hi)
{
  if (lo >= hi) return(0);

  lli inversions = 0, mid = (lo + hi) / 2;
  inversions += mergeSort(array, lo, mid);
  inversions += mergeSort(array, mid + 1, hi);
  inversions += merge(array, lo, mid, hi);
  return(inversions);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    int array[n];
    for (int i = 0; i < n; i ++)
      scanf("%d", &array[i]);

    lli inversions = mergeSort(array, 0, n - 1);
    DEBUG printArray(array, 0, n - 1);
    printf("%lld\n", inversions);
  }
  return(0);
}