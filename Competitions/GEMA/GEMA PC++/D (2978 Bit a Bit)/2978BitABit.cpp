#include <bits/stdc++.h>

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    int ans[32]; memset(ans, -1, sizeof(ans));
    for (int k = 0; k < n; k ++)
    {
      char op[10];
      scanf(" %s", op);
      if (!strcmp(op, "CLEAR"))
      {
        int i; scanf("%d", &i);
        ans[i] = 0;
      }
      if (!strcmp(op, "SET"))
      {
        int i; scanf("%d", &i);
        ans[i] = 1;
      }
      if (!strcmp(op, "OR"))
      {
        int i, j; scanf("%d %d", &i, &j);
        if (ans[i] == 1 || ans[j] == 1)
          ans[i] = 1;
        else if ((ans[i] == 0 && ans[j] == -1) || (ans[j] == 0 && ans[i] == -1))
          ans[i] = -1;
        else; // both are 0
      }
      if (!strcmp(op, "AND"))
      {
        int i, j; scanf("%d %d", &i, &j);
        if (ans[i] == 0 || ans[j] == 0)
          ans[i] = 0;
        else if ((ans[i] == 1 && ans[j] == -1) || (ans[j] == 1 && ans[i] == -1))
          ans[i] = -1;
        else; // both are 1
      }
    }
    for (int i = 31; i >= 0; i --) printf("%c", ans[i] == -1 ? '?' : ans[i] + '0');
    printf("\n");
  }
  return 0;
}