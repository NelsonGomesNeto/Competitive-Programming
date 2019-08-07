#include <bits/stdc++.h>
using namespace std;

int binSearch(int array[], int lo, int hi, int target)
{
  int mid = lo + (hi - lo) / 2;
  if (lo >= hi)
  {
    if (array[mid] <= target)
      return(mid + 1);
    return(mid);
  }
  if (array[mid] <= target)
    return(binSearch(array, mid + 1, hi, target));
  return(binSearch(array, lo, mid, target));
}

int main()
{
  int numShops; scanf("%d", &numShops);
  int shops[numShops];
  for (int i = 0; i < numShops; i ++)
    scanf("%d", &shops[i]);
  sort(shops, shops + numShops);
  int days, money; scanf("%d", &days);
  for (int i = 0; i < days; i ++)
  {
    scanf("%d", &money);
    printf("%d\n", binSearch(shops, 0, numShops - 1, money));
  }
  return(0);
}