#include <stdio.h>

int main()
{
  int C1, C2, C3, C4, C5;
  scanf("%d %d %d %d %d", &C1, &C2, &C3, &C4, &C5);
  if (C1 >= C2 && C2 >= C3 && C3 >= C4 && C4 >= C5)
  {
    printf("D\n");
  }
  else if (C1 <= C2 && C2 <= C3 && C3 <= C4 && C4 <= C5)
  {
    printf("C\n");
  }
  else
  {
    printf("N\n");
  }
  return(0);
}
