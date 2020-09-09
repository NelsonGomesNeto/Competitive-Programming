#include <bits/stdc++.h>
using namespace std;

int minimum(int a[], int lo, int hi)
{
  int m = 1 << 20;
  for (int i = lo; i <= hi; i ++) m = min(m, a[i]);
  return(m);
}

int main()
{
  int n; scanf("%d", &n);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);

  int lo, hi;
  while (scanf("%d %d", &lo, &hi) != EOF)
    printf("[%d, %d] = %d\n", lo, hi, minimum(a, lo, hi));
  return(0);
}
