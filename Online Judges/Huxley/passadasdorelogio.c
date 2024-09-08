#include <stdio.h>

int main()
{
  int hI, mI, hF, mF, passadas = 0, already = 0, limit;
  scanf("%d %d %d %d", &hI, &mI, &hF, &mF);
  if (mI >= hI * 5 && already == 0)
  {
    already = 1;
  }
  while (!(hI == hF && mI == mF))
  {
    mI ++;
    if (mI == 60)
    {
      mI = 0;
      hI ++;
      if (hI > 12)
      {
        hI = 1;
      }
      already = 0;
    }
    if (mI >= hI * 5 && already == 0)
    {
      passadas ++;
      already = 1;
    }
  }
  printf("%d\n", passadas);
  return(0);
}
