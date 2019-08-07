#include <bits/stdc++.h>

char s[100005];

int main()
{
  scanf("%s", s);

  int a = 0, b = 0, c = 0, d = 0;
  for (int i = 0; s[i + 1]; i ++)
  {
    if (s[i] == 'A' && s[i + 1] == 'B' && !a)
    {
      a = 1;
      i ++;
    }
    else if (s[i] == 'B' && s[i + 1] == 'A' && a)
      b = 1;
  }
  for (int i = 0; s[i + 1]; i ++)
  {
    if (s[i] == 'B' && s[i + 1] == 'A' && !d)
    {
      d = 1;
      i ++;
    }
    else if (s[i] == 'A' && s[i + 1] == 'B' && d)
      c = 1;
  }

  printf("%s\n", (a && b) || (c && d) ? "YES" : "NO");

  return(0);
}