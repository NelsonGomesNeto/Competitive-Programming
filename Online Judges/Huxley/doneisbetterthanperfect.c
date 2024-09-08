#include <stdio.h>

int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    int hora, min, work; scanf("%d:%d %d", &hora, &min, &work);
    int rH = hora, rM = min, now = work;
    while (now > 0)
    {
      rM --; now --;
      if (rM < 0)
      {
        rH --;
        rM = 59;
      }
      if (rH < 0)
      {
        rH = 23;
      }
    }
    printf("%02d:%02d ", rH, rM);
    rH = hora; rM = min;
    while (now < work)
    {
      rM ++; now ++;
      if (rM > 59)
      {
        rH ++;
        rM = 0;
      }
      if (rH > 23)
      {
        rH = 0;
      }
    }
    printf("%02d:%02d\n", rH, rM);
    tests --;
  }
}
