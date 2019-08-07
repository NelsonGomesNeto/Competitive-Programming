#include <stdio.h>

int main()
{
  int n; scanf("%d", &n);
  int hole[n], i; for (i = 0; i < n; i ++) scanf("%d", &hole[i]);

  int biggest = 0, now = 0;
  for (i = 0; i < n; i ++)
  {
    int size = 1, origin = i;
    for (now = hole[i]; now != origin; now = hole[now])
      size ++;
    if (size > biggest)
      biggest = size;
  }

  printf("%d\n", biggest);
  return(0);
}
