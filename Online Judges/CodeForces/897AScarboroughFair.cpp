#include <bits/stdc++.h>

int main()
{
  int size, n; scanf("%d %d\n", &size, &n);
  char s[size + 1], f, t;
  scanf("%s", s);
  int l, r;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d %c %c", &l, &r, &f, &t);
    for (int j = l - 1; j < r; j ++)
      if (s[j] == f)
        s[j] = t;
  }

  printf("%s\n", s);
  return(0);
}