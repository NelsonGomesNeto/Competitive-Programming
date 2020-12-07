#include <bits/stdc++.h>
#define DEBUG if(0)

int main()
{
  int n; scanf("%d", &n);
  int a[n], zero = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%1d", &a[i]);
    zero += !a[i];
  }
  DEBUG for (int i = 0; i < n; i ++)
    printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
  if (n == 1)
    printf("%d", a[0]);
  else
  {
    printf("1");
    for (int i = 0; i < zero; i ++)
      printf("0");
  } printf("\n");
  return(0);
}