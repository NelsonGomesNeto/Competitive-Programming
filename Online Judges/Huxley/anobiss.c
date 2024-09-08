#include <stdio.h>

int main()
{
  int naohouve = 0, anoini, anofinal;
  scanf("%i %i", &anoini, &anofinal);
  while (anoini <= anofinal)
  {
    if (( (anoini % 4 == 0) && (anoini % 100 != 0) ) || (anoini % 400 == 0))
    {
      printf("%i\n", anoini);
      naohouve ++;
    }
    anoini ++;
  }
  if (naohouve == 0)
  {
    printf("-1\n");
  }
  return(0);
}
