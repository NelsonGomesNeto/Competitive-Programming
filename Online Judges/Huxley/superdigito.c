#include <stdio.h>
#include <string.h>

int main()
{
  char super[1000000], aux[1000000]; int muda, ler, vezes;
  scanf("%s", super);
  strcpy(aux,super);
  scanf("%d", &vezes);
  while (vezes > 1)
  {
    strcat(super,aux);
    vezes --;
  }
  while (strlen(super) > 1)
  {
    muda = 0;
    for (ler = 0; ler < strlen(super); ler ++)
    {
      muda += (int) super[ler] - 48;
    }
    sprintf(super, "%d", muda);
  }
  printf("%s\n", super);
  return(0);
}
