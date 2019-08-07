#include <stdio.h>

int main()
{
  int c, n; scanf("%d %d", &c, &n);
  int olives[n + 1]; for (int i = 0; i < n; i ++) scanf("%d", &olives[i]);
  olives[n] = c + olives[0];

  int spacing = c / n, can = 1;
  n ++; // test without this
  for (int start = olives[0]; start <= olives[0] + spacing; start ++)
  {
    int pos = start + spacing; can = 1;
    for (int j = 1; j < n; j ++)
    {
      if (olives[j] > pos || olives[j] + spacing <= pos)
      { can = 0; break; }
      pos += spacing;
    }
    if (can) break;
  }
  printf("%c\n", can ? 'S' : 'N');

  return(0);
}