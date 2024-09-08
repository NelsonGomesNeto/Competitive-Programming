#include <stdio.h>

int main()
{
  int num1, num2, mmc, back;
  scanf("%d %d", &num1, &num2);
  mmc = num1;
  back = num1;
  while (mmc % num1 > 0 || mmc % num2 > 0)
  {
    mmc += back;
  }
  printf("%d\n", mmc);
}
