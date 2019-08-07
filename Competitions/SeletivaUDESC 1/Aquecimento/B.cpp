#include <bits/stdc++.h>

int main()
{
  int e, d;
  while (scanf("%d %d", &e, &d) && !(!e && !d))
  {
    if (e < 0 || d < 0)
      printf("Og diz: Eh um NP!\n");
    else
      printf("%d\n", e + d);
  }
  return(0);
}