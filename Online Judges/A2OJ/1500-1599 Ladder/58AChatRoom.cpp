#include <bits/stdc++.h>
char word[6] = "hello";

int main()
{
  char s[101]; scanf("%s", s);

  int can = 0, i = 0;
  for (int at = 0; at < 5; at ++)
  {
    while (s[i] && s[i] != word[at]) i ++;
    if (!s[i]) break;
    if (at == 2 && s[i] && s[i] == word[at]) { i ++; continue; }
    while (s[i] && s[i] == word[at]) i ++;
    if (at == 4) can = 1;
  }

  printf("%s\n", can ? "YES" : "NO");

  return(0);
}