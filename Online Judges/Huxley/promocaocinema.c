#include <stdio.h>

int main()
{
  int idade, graca = 0;
  char gender = 'n';
  scanf("%i", &idade);
  while (idade != 111)
  {
    if ((gender == 'm' && idade > 25 && idade < 35) ||
    (gender == 'M' && idade > 25 && idade < 35) ||
    (idade <= 10  || idade > 60) && idade != 111 && idade != 0)
    {
      idade = 60;
      graca ++;
    }
    scanf("%c", &gender);
    scanf("%i", &idade);
  }
  printf("%i\n", graca);
  return(0);
}
