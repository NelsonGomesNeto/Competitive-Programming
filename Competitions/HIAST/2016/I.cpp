#include <bits/stdc++.h>
char a[(int) 1e5 + 1], b[(int) 1e5 + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("\n%s\n%s", a, b);
    int la[256], lb[256]; memset(la, 0, sizeof(la)); memset(lb, 0, sizeof(lb));
    for (int i = 0; a[i]; i ++) la[a[i]] ++;
    for (int i = 0; b[i]; i ++) lb[b[i]] ++;

    int ans = 0;
    for (int i = 0; i < 256; i ++) ans += abs(la[i] - lb[i]);
    printf("%d\n", ans);
  }
  return(0);
}
