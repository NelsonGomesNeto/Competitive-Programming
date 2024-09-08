#include <stdio.h>

int main()
{
  int idade1, idade2;
  scanf("%i\n%i", &idade1, &idade2);
  if (idade1 % 2 == 0 && idade2 % 2 == 0)
  {
      printf("desconto\n");
  }
}
