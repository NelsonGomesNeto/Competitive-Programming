#include <stdio.h>

int main()
{
  int IA, IB, FA, FB, change = 0;
  scanf("%d %d %d %d", &IA, &IB, &FA, &FB);
  /*if ((IA != FA && IB != FB) || (IA != FB && IA == FA))
  {
    printf("1\n");
  }
  else if (IA == FA && IB != FB)
  {
    printf("2\n");
  }
  else
  {
    printf("0\n");
  }*/
  if ((IA == FA && IB != FB) || (IA != FA && IB == FB) || (IB != FB && IA == FA))
  {
    change ++;
  }
  if ((IA != FA && IB != FB) || (IB != FB && IA == FA))
  {
    change ++;
  }
  printf("%d\n", change);
  return(0);
}
