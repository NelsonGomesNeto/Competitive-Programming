#include <stdio.h>

int main()
{
  int idade, saram = 0, hepa = 0, both = 0;
  while (scanf("%i", &idade) && idade != 100)
  {
    if (idade >= 3 && idade <= 6)
    {
      saram ++;
    }
    if (idade >= 5 && idade <= 8)
    {
      hepa ++;
    }
    if (idade >= 5 && idade <= 6)
    {
      both ++;
    }
  }
  printf("%i\n%i\n%i\n", saram, hepa, both);
  return(0);
}
