#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int array[n], ones = 0, i;
  for (i = 0; i < n; i ++) scanf("%d", &array[i]);

  int biggest = -1, now = 0;

  for (i = 0; i < n; i ++)
  {
    ones += array[i];
    now += array[i] ? -1 : 1;
    biggest = max(biggest, now);
    if (now < 0) now = 0;
  }

  printf("%d\n", ones + biggest);

  return(0);
}