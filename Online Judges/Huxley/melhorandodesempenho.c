#include <stdio.h>

int main()
{
  float nota, melhora, repeat = 0, brinquedo = 1;
  scanf("%f", &nota);
  while (repeat < 5)
  {
    melhora = nota;
    scanf("%f", &nota);
    melhora = nota - melhora;
    if (melhora > 0)
    {
      brinquedo ++;
    }
    else
    {
      brinquedo --;
    }
    repeat ++;
  }
  if (brinquedo == 6)
  {
    printf("Ganha brinquedo\n");
  }
  else
  {
    printf("Sem brinquedo\n");
  }
  return(0);
}
