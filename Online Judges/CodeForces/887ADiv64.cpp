#include <bits/stdc++.h>

int main()
{
  char string[1000];
  scanf("%s", string);
  int size = strlen(string), i, can = 0, before = 0;
  for (i = size - 1; i >= 0; i --)
  {
    //printf("%d %c\n", size - i, string[i]);
    if (size - i  - before >= 7 && string[i] == '1') can = 1;
    if (string[i] == '1') before ++;
  }

  printf("%s\n", can ? "yes" : "no");

  return(0);
}