#include <stdio.h>

int main()
{
  float IPVA, taxa, total;
  scanf("%f\n%f", &IPVA, &taxa);
  total = (IPVA * 0.95) + taxa;
  printf("%.2f\n", total);
  return(0);
}
