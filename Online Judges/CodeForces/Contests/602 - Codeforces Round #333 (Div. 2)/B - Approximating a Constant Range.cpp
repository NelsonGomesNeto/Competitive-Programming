#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

void printArray(int a[], int size)
{
  for (int i = 0; i < size; i ++) printf("%d%c", a[i], i < size - 1 ? ' ' : '\n');
}

void printSet(set<int> s)
{
  for (auto i: s) printf("%d ", i);
  printf("\n");
}

int validRange(set<int> range)
{
  if (range.empty()) return(1);
  return((*range.rbegin() - *range.begin()) <= 1);
}

int main()
{
  int n; scanf("%d", &n);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);

  int last[100001], lo = 0, hi = 0, minimum = a[0], maximum = a[0], ans = 1;
  while (hi < n)
  {
    last[a[hi]] = hi;
    while (hi + 1 < n && a[hi] == a[hi + 1]) hi ++;
    maximum = max(maximum, a[hi]);
    minimum = min(minimum, a[hi]);
    DEBUG printf("%d %d %d %d\n", lo, hi, maximum, minimum);
    if (maximum - minimum > 1)
    {
      if (minimum == a[hi])
      {
        lo = last[a[hi] + 1];
        maximum = a[hi] + 1;
      }
      else if (maximum == a[hi])
      {
        lo = last[a[hi] - 1];
        minimum = a[hi] - 1;
      }
    }
    ans = max(ans, hi - lo + 1);
    hi ++;
  }

  printf("%d\n", ans);

  return(0);
}