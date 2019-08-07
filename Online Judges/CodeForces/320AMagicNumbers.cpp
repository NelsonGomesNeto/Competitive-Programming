#include <bits/stdc++.h>

int main()
{
  int num, start = 0, four = 0, magic = 1;
  while (scanf("%01d", &num) != EOF)
  {
    if (start ++ == 0 && num == 4) magic = 0;
    if (num == 4)
      four ++;
    else
      four = 0;
    if (!(num == 1 || num == 4)) magic = 0;
    if (four > 2) magic = 0;
  }

  printf("%s\n", magic ? "YES" : "NO");

  return(0);
}