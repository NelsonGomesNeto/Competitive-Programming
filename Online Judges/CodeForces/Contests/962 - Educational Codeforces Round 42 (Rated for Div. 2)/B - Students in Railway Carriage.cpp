#include <bits/stdc++.h>
#define DEBUG if(0)

int main()
{
  int n, a, b; scanf("%d %d %d", &n, &a, &b);
  if (a < b) { int aux = a; a = b; b = aux; }
  char room[n + 1]; scanf("\n%s", room);

  int total = 0, begin = 0;
  for (int i = 0; i < n; i ++)
  {
    DEBUG printf("%d %d %d\n", a, b, total);
    if (room[i] == '.' && begin)
    {
      begin = 1 - begin;
      if (b) { b --; total ++; }
      if (a < b) { int aux = a; a = b; b = aux; begin = 1 - begin; }
    }
    else if (room[i] == '.' && !begin)
    {
      begin = 1 - begin;
      if (a) { a --; total ++; }
      if (a < b) { int aux = a; a = b; b = aux; begin = 1 - begin; }
    }
    else if (room[i] == '*') begin = 0;
  }

  printf("%d\n", total);

  return(0);
}