#include <stdio.h>

int main()
{
  double hotdogs, participants;
  scanf("%lf %lf", &hotdogs, &participants);
  double ratio = hotdogs / participants;

  printf("%.2lf\n", ratio);
  return(0);
}
