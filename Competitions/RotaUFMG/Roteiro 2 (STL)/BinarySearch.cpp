#include <bits/stdc++.h>
using namespace std;

int lowerBound(int array[], int lo, int hi, int target)
{
  if (lo >= hi) return(array[lo] == target ? lo : -1);
  int mid = (lo + hi) / 2;
  if (target <= array[mid]) return(lowerBound(array, lo, mid, target));
  else return(lowerBound(array, mid + 1, hi, target));
}

int main()
{
  int n, q; scanf("%d %d", &n, &q);
  int array[n], query;
  for (int i = 0; i < n; i ++)
    scanf("%d", &array[i]);

  while (q -- > 0)
  {
    scanf("%d", &query);
    int pos = lowerBound(array, 0, n - 1, query);
    printf("%d\n", pos);
  }

  return(0);
}