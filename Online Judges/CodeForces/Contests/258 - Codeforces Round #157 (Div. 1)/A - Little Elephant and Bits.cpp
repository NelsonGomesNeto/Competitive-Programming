#include <bits/stdc++.h>

int main()
{
  int first = 1; char num, prev = '2';
  while (scanf("%c", &num) && num != '\n')
  {
    if (first && num == '0') { first = 0; continue; }
    if (prev != '2') printf("%c", prev);
    prev = num;
  }
  if (first) printf("\n");
  else printf("%c\n", prev);

  return(0);
}