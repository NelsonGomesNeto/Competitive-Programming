#include <stdio.h>

int main()
{
  long long int num;
  while (scanf("%Ld", &num) != EOF)
  {
    long long int digits = (num * 2) - 1;
    long long int last = ((digits * digits) / 2) + digits - 0.5;
    long long int soma = (last - 4) + (last - 2) + last;
    soma = soma < 0 ? 1 : soma;
    printf("%Ld\n", soma);
  }
  return(0);
}
/*No UVA é:
#include <stdio.h>

int main()
{
  long double digits;
  while (scanf("%Lf", &digits) != EOF)
  {
    long double line = (digits + 1) / 2;
    long double last = 2 * (line * (line + 1) - line) - 1;
    long double soma = (last - 4) + (last - 2) + last;
    soma = soma < 0 ? 1 : soma;
    printf("%.0Lf\n", soma);
  }
  return(0);
}*/
