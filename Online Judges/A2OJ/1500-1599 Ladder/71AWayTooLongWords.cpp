#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  while (n --)
  {
    char s[101]; scanf("\n%s", s);
    int size = strlen(s);
    if (size > 10) printf("%c%d%c\n", s[0], size - 2, s[size - 1]);
    else printf("%s\n", s);
  }
  return(0);
}