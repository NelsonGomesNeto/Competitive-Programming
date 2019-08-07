#include <stdio.h>
#include <string.h>
#include <math.h>
#define lli unsigned long long int

int main()
{
  long double valor; scanf("%Lf", &valor);
  lli base = (lli) (valor * 100); char dinheiros[100];
  int i, j, tam = (int) log10(base);
  strcpy(dinheiros, "R$ "); j = 3; i = tam + 1;
  if (i > 2)
  {
    for (i = tam + 1; i > 0 ; i --, j ++)
    {
      dinheiros[j] = ((base % (lli) (pow(10, i))) / (lli) pow(10, i - 1)) + '0';
      if (i == 3)
      {
        j ++; dinheiros[j] = ','; continue;
      }
      if ((i) % 3 == 0)
      {
        j ++; dinheiros[j] = '.';
      }
    }
  }
  else
  {
    dinheiros[j] = '0'; j ++;
    dinheiros[j] = ','; j ++;
    dinheiros[j] = ((base % 100) / 10) + '0'; j ++;
    dinheiros[j] = (base % 10) + '0'; j ++;
  }
  dinheiros[j] = '\0';
  printf("%s\n", dinheiros);
  return(0);
}
