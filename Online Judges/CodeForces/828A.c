#include <stdio.h>

int main()
{
  int groups, one, two, twoSingle = 0;
  scanf("%d %d %d", &groups, &one, &two);
  int people = 0, i, x;
  for (i = 0; i < groups; i ++)
  {
    scanf("%d", &x);

    if (x == 2 && two > 0)
      two --;
    else if (x == 2)
      people += 2;

    if (x == 1 && one > 0)
      one --;
    else if (x == 1 && two > 0)
    {
      two --;
      twoSingle ++;
    }
    else if (x == 1 && twoSingle > 0)
      twoSingle --;
    else if (x == 1)
      people ++;
  }

  printf("%d\n", people);

  return(0);
}
