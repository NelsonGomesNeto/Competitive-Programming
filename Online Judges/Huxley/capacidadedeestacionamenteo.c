#include <stdio.h>

int main()
{
  int vagas; float ganho;
  scanf("%d", &vagas);
  ganho = (42 - vagas) * 1.75;
  printf("%.2f\n", ganho);
  return(0);
}
