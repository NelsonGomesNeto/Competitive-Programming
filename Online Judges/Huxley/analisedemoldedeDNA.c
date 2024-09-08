#include <stdio.h>

int main()
{
  int codigo, check, monstro = 0, maior = 0, codigoMonstro; char DNA[30];
  while (scanf("%d", &codigo) && codigo != 9999)
  {
    getchar();
    scanf("%[^\n]", &*DNA);
    for (check = 0; check < 30; check ++)
    {
      if (DNA[check] == 'T')
      {
        monstro ++;
      }
    }
    if (monstro > maior)
    {
      maior = monstro;
      codigoMonstro = codigo;
    }
  }
  printf("%d\n", codigoMonstro);
  return(0);
}
