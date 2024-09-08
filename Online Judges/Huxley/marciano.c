#include <stdio.h>
#include <math.h>

int main()
{
  int L, H, P, R, diag2D, diag3D; scanf("%d %d %d %d", &L, &H, &P, &R);
  diag2D = sqrt(pow(L,2) + pow(H,2));
  diag3D = sqrt(pow(diag2D,2) + pow(P,2));
  //if (L > 2 * R || H > 2 * R || P > 2 * R || (L * H * P > (double) (4 * acos(-1) * pow (R,3)) / 3))
  if (diag3D > 2 * R)
  {
    printf("N\n");
  }
  else
  {
    printf("S\n");
  }
  return(0);
}
