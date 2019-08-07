#include <bits/stdc++.h>

void lolXor(char a[], char b[], char c[])
{
  for (int i = 0; a[i]; i ++) c[i] = (a[i] != b[i]) + '0';
}

int main()
{
  char a[101], b[101], c[101]; scanf("%s\n%s", a, b);
  memset(c, 0, sizeof(c)); lolXor(a, b, c);
  printf("%s\n", c);

  return(0);
}