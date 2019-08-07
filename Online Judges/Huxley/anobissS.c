#include <stdio.h>

int main()
{
  int ano;
  scanf("%i", &ano);
  if (( (ano % 4 == 0) && (ano % 100 != 0) ) || (ano % 400 == 0))
  {
    printf("BISSEXTO\n");
  }
  else
  {
    printf("NAOBISSEXTO\n");
  }
  return(0);
}
