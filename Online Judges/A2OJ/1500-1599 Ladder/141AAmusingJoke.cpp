#include <bits/stdc++.h>

void read(int a[])
{
  char l;
  while (scanf("%c", &l) && l != '\n') a[l] ++;
}

int main()
{
  int a[256], b[256], c[256];
  memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b)); memset(c, 0, sizeof(c));
  read(a); read(b); read(c);

  for (int i = 0; i < 256; i ++)
  {
    while (c[i] && a[i])
    {
      a[i] --;
      c[i] --;
    }
    while (c[i] && b[i])
    {
      b[i] --;
      c[i] --;
    }
  }

  int can = 1;
  for (int i = 0; i < 256; i ++)
    if (a[i] || b[i] || c[i]) can = 0;
  printf("%s\n", can ? "YES" : "NO");

  return(0);
}