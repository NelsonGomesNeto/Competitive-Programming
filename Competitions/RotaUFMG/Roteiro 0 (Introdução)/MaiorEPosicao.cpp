#include <bits/stdc++.h>

int main()
{
  int n, biggest = -1e7, pos;
  for (int i = 0; i < 100; i ++)
  {
    scanf("%d", &n);
    if (n > biggest)
    {
      biggest = n;
      pos = i + 1;
    }
  }

  printf("%d\n%d\n", biggest, pos);

  return(0);
}