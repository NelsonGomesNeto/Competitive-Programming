#include <stdio.h>
#include <math.h>

int main()
{
  long long int selos; int check;
  scanf("%Ld\n", &selos);

  double limit = sqrt(selos);
  for (check = 2; check < limit; check ++)
  {
    if (selos % check == 0)
    {
      printf("S\n");
      return(0);
    }
  }
  printf("N\n");
  return(0);
}
