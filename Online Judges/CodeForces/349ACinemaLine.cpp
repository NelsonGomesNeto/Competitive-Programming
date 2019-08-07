#include <bits/stdc++.h>
int d[3] = {25, 50, 100};

int main()
{
  int n; scanf("%d", &n);
  int each[101], x, can = 1; memset(each, 0, sizeof(each));
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &x); each[x] ++; x -= 25;
    for (int j = 2 - 1; j >= 0; j --)
      while (each[d[j]] && x >= d[j])
      {
        each[d[j]] --;
        x -= d[j];
      }
    if (x) can = 0;
  }
  printf("%s\n", can ? "YES" : "NO");
  return(0);
}