#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxK = 1e6; int k;
char s[maxK + 1];
int accSum[maxK + 1], sSize;

int binarySearch(int lo, int hi, int target, bool upperBound)
{
  if (lo >= hi) return(lo);
  while (lo < hi)
  {
    int mid = ((lo + hi) >> 1) + (upperBound ? ((lo + hi) & 1) : 0);
    if (upperBound)
    {
      if (accSum[mid] <= target) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (accSum[mid] >= target) hi = mid;
      else lo = mid + 1;
    }
  }
  return(lo);
}

int main()
{
  scanf("%d\n%s", &k, s); sSize = strlen(s);
  for (int i = 0; i < sSize; i ++) accSum[i + 1] = (s[i] == '1') + accSum[i];
  lli total = 0;
  if (k)
    for (int i = 0; i < sSize; i ++)
    {
      if (s[i] == '0') continue;
      int start = binarySearch(i, sSize, accSum[i] + k, false);
      if (accSum[start] - accSum[i] < k) continue;
      // printf("%d %d | %d %d\n", i, start - 1, accSum[i], accSum[start]);
      total += (lli) (i - binarySearch(0, i, accSum[i], false) + 1) * (binarySearch(i, sSize, accSum[start], true) - start + 1);
    }
  else
    for (int i = 0; i < sSize; i ++)
      if (s[i] == '0')
        total += binarySearch(i, sSize, accSum[i], true) - i;

  printf("%lld\n", total);
  return(0);
}