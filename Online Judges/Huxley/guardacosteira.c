#include <stdio.h>
#include <math.h>

int main()
{
  float D, VF, VG, tF, tG, DG;
  while (scanf("%f %f %f", &D, &VF, &VG) && D != -1 && VF != -1 && VG != -1)
  {
    DG = sqrt(pow(12,2) + pow(D,2));
    tG = DG / VG;
    tF = 12 / VF;
    if (tG <= tF)
    {
      printf("S\n");
    }
    else
    {
      printf("N\n");
    }
  }
  return(0);
}
