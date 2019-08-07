#include <bits/stdc++.h>

int dangerous(char p[])
{
  for (int i = 0; p[i];)
  {
    int now = p[i], d = 0;
    while (p[i] && p[i] == now) i ++, d ++;
    if (d >= 7) return(1);
  }
  return(0);
}

int main()
{
  char p[101]; scanf("%s", p);
  printf("%s\n", dangerous(p) ? "YES" : "NO");
  return(0);
}