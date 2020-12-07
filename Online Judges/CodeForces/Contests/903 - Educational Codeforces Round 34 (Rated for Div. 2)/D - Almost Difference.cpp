#include <bits/stdc++.h>
#define DEBUG if(1)
using namespace std;

int d(int x, int y)
{
  if (abs(x - y) > 1) return(y - x);
  else return(0);
}

int main()
{
  int n; scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; i ++)
    scanf("%d", &a[i]);

  DEBUG for (int i = 0; i < n; i ++)
    printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');

  int sum = 0, prev = 0;
  for (int i = 1; i < n; i ++)
    prev += d(a[0], a[i]);

  for (int i = 1; i < n; i ++)
  {
    if (a[i] > a[i - 1] + 1)
    else if (a[i] >= a[i - 1])
    else if (a[i] < a[i - 1])
  }

  printf("%d\n", sum);

  return(0);
}