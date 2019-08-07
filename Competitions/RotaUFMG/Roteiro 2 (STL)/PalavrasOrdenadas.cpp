#include <bits/stdc++.h>

int main()
{
  int p; scanf("%d", &p);
  while (p -- > 0)
  {
    int sorted = 1; char s[100];
    scanf("\n%s", s);
    for (int i = 1; s[i]; i ++)
      if (tolower(s[i - 1]) >= tolower(s[i]))
        sorted = 0;

    printf("%s: %c\n", s, sorted ? 'O' : 'N');
  }
  return(0);
}