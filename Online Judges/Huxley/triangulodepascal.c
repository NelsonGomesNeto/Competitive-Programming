#include <stdio.h>
#include <string.h>

int main()
{
  int n; scanf("%d", &n);
  int prv[n + 1], nxt[n + 1], i, j; prv[0] = prv[1] = 1;
  if (n) printf("1\n1 1\n"); else printf("1\n");
  for (i = 1; i < n; i ++)
  {
    nxt[0] = nxt[i + 1] = 1;
    for (j = 0; j < i; j ++)
      nxt[j + 1] = prv[j] + prv[j + 1];
    for (j = 0; j <= i + 1; j ++)
      printf("%d%c", nxt[j], j < i + 1 ? ' ' : '\n');
    memcpy(prv, nxt, sizeof(prv));
  }
  return(0);
}
