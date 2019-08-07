#include <bits/stdc++.h>
using namespace std;

void printArray(int a[], int size)
{
  for (int i = 0; i < size; i ++)
    printf("%d%c", a[i], i < size - 1 ? ' ' : '\n');
}

int lowerBound(int array[], int tail[], int lo, int hi, int target)
{
  if (lo >= hi) return(lo);
  int mid = (lo + hi) / 2;
  if (target <= array[tail[mid]]) return(lowerBound(array, tail, lo, mid, target));
  else return(lowerBound(array, tail, mid + 1, hi, target));
}

int lis(int array[], int ans[], int size)
{
  int lisSize = 0, tail[size + 1], prev[size + 1];
  tail[0] = tail[1] = 0;

  for (int i = 0; i < size; i ++)
  {
    int pos;
    if (array[i] < array[tail[1]])
      pos = 1;
    else if (array[i] > array[tail[lisSize]])
      pos = lisSize + 1;
    else
      pos = lowerBound(array, tail, 1, lisSize, array[i]);

    prev[i] = tail[pos - 1];
    tail[pos] = i;

    if (pos > lisSize) lisSize = pos;
  }
  for (int i = tail[lisSize], k = lisSize - 1; k >= 0; k --, i = prev[i])
    ans[k] = array[i];
  return(lisSize);
}

int main()
{
  int first, t = 0;
  while (scanf("%d", &first) && first != -1)
  {
    if (t ++) printf("\n");

    int other, array[(int) 1e6], size = 1; array[0] = first;
    while (scanf("%d", &other) && other != -1)
      array[size ++] = other;

    reverse(array, array+size);
    int ans[size];
    int lisSize = lis(array, ans, size);
    //printArray(ans, lisSize);
    printf("Test #%d:\n  maximum possible interceptions: %d\n", t, lisSize);
  }
  return(0);
}