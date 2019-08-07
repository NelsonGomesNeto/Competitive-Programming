#include <bits/stdc++.h>
using namespace std;

int upperBound(int array[], int lo, int hi, int target)
{
  if (lo >= hi - 1) return(array[hi] == target ? hi : array[lo] == target ? lo : -1);
  int mid = (lo + hi) / 2;
  if (target < array[mid]) return(upperBound(array, lo, mid - 1, target));
  else return(upperBound(array, mid, hi, target));
}

int lowerBound(int array[], int lo, int hi, int target)
{
  if (lo >= hi) return(array[lo] == target ? lo : 0);
  int mid = (lo + hi) / 2;
  if (target <= array[mid]) return(lowerBound(array, lo, mid, target));
  else return(lowerBound(array, mid + 1, hi, target));
}

int main()
{
  int n; scanf("%d", &n);
  int array[n][4], possibleSums[2][n*n];
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < 4; j ++)
      scanf("%d", &array[i][j]);

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      possibleSums[0][i + j*n] = array[i][0] + array[j][1];
      possibleSums[1][i + j*n] = array[i][2] + array[j][3];
    }

  sort(possibleSums[0], possibleSums[0]+(n*n));
  sort(possibleSums[1], possibleSums[1]+(n*n));

  int zeros = 0;
  for (int i = 0; i < n*n; i ++)
  {
    //printf("%d %d\n", upperBound(possibleSums[1], 0, n*n - 1, -possibleSums[0][i]), lowerBound(possibleSums[1], 0, n*n - 1, -possibleSums[0][i]));
    //zeros += upperBound(possibleSums[1], 0, n*n - 1, -possibleSums[0][i]) - lowerBound(possibleSums[1], 0, n*n - 1, -possibleSums[0][i]) + 1;
    zeros += upper_bound(possibleSums[1], possibleSums[1]+(n*n), -possibleSums[0][i]) - lower_bound(possibleSums[1], possibleSums[1]+(n*n), -possibleSums[0][i]);
  }
  printf("%d\n", zeros);

  return(0);
}