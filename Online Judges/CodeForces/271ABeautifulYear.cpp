#include <bits/stdc++.h>

int verify(int n)
{
  int digits[10]; memset(digits, 0, sizeof(digits));
  while (n > 0)
  {
    digits[n % 10] ++;
    n /= 10;
  }
  for (int i = 0; i < 10; i ++)
    if (digits[i] > 1) return(0);
  return(1);
}

int main()
{
  int year; scanf("%d", &year); year ++;

  while (!verify(year)) year ++;

  printf("%d\n", year);

  return(0);
}