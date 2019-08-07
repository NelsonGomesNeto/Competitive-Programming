#include <bits/stdc++.h>

int main()
{
  int in[1000001];
  int n;
  while (scanf("%d", &n) && n)
  {
    memset(in, 0, sizeof(in));
    int a, b;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d %d", &a, &b);
      in[a] ++; in[b] --;
    }
    int can = 1;
    for (int i = 0; i < n && can; i ++) if (in[i]) can = 0;
    printf("%s\n", can ? "YES" : "NO");
  }
  return(0);
}