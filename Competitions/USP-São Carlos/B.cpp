#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  char s[n + 2]; memset(s, 0, sizeof(s)); scanf("\n%s", s);
  int ugly = 1, ugly2 = 1, at = s[0], f = s[0];
  for (int i = 1; s[i]; i ++)
  {
    if (at > s[i])
      ugly = 0;
    if (f >= s[i] && !ugly)
      ugly2 = 0;
    at = s[i];
  }
  ugly |= ugly2;
  printf("%s\n", ugly ? "Yes" : "No");
}1212