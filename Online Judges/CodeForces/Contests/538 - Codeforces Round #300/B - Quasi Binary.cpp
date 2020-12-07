#include <bits/stdc++.h>
using namespace std;

int main()
{
  int num; scanf("%d", &num);
  int aux = num;

  int minimum = 0;
  while (aux > 0)
  {
    minimum = max(minimum, aux % 10);
    aux /= 10;
  }

  printf("%d\n", minimum);
  while (minimum -- > 0)
  {
    int i = 1, ans = 0; aux = num;
    while (aux > 0)
    {
      ans += (aux % 10 > 0) * i;
      i *= 10;
      aux /= 10;
    }
    num -= ans;
    printf("%d%c", ans, minimum > 0 ? ' ' : '\n');
  }

  return(0);
}