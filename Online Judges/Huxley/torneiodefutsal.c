#include <stdio.h>

int main()
{
  float premio, st1, nd2, rd3;
  scanf("%f", &premio);
  st1 = premio * 0.6;
  nd2 = premio * 0.3;
  rd3 = premio * 0.1;
  printf("%.2f\n%.2f\n%.2f\n", st1, nd2, rd3);
  return(0);
}
