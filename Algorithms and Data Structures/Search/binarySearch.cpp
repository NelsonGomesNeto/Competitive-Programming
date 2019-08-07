#include <bits/stdc++.h>
using namespace std;
const int maxSize = 1e6;
int a[maxSize], n;

void printAns(int pos)
{
  for (int i = 0; i < n; i ++) printf(" %4d", a[i]);
  printf("\n      %4d:",pos); for (int i = 0; i < pos; i ++) printf("     ");
  printf("    ^\n");
}

int lowerBound(int lo, int hi, int target)
{
  if (lo >= hi) return(lo);
  int mid = (lo + hi) >> 1;
  if (target <= a[mid]) return(lowerBound(lo, mid, target));
  return(lowerBound(mid + 1, hi, target));
}

int upperBound(int lo, int hi, int target)
{
  if (lo >= hi) return(lo);
  int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  if (target < a[mid]) return(upperBound(lo, mid - 1, target));
  return(upperBound(mid, hi, target));
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  sort(a, a+n);

  int target;
  while (scanf("%d", &target) != EOF)
  {
    printf("\nQuery: %d\n", target);
    int lo = lowerBound(0, n - 1, target), hi = upperBound(0, n - 1, target);
    printf("lowerBound:"); printAns(lo);
    printf("upperBound:"); printAns(hi);
  }
  return(0);
}
