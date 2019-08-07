#include <bits/stdc++.h>

int lowerBound(int array[], int lo, int hi, int target)
{
  if (lo >= hi) return(array[lo] == target ? lo : -1);
  int mid = (lo + hi) / 2;
  if (target <= array[mid]) return(lowerBound(array, lo, mid, target));
  else return(lowerBound(array, mid + 1, hi, target));
}

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    int x[n], d[n + 1]; d[0] = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &x[i]);
      d[i + 1] = d[i] + x[i];
    }

    int side = d[n] / 3, triangles = 0;
    for (int i = 0; i < n; i ++)
    {
      int j = lowerBound(d, i + 1, n - 1, d[i] + side), k = -1;
      if (j != -1)
        k = lowerBound(d, j + 1, n - 1, d[j] + side);
      //printf("%d %d %d %d %d %d\n", i, j, k, d[i], d[j], d[k]);
      if (j != -1 && k != -1 && (d[j] - d[i] == side) && (d[k] - d[j] == side) && (d[n] - d[k] + d[i] == side))
        triangles ++;
    }
    printf("%d\n", triangles);
  }
  return(0);
}