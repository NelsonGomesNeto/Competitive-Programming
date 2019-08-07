#include <stdio.h>

int main()
{
  int num1, num2, aux, checknum, teste, nao; scanf("%d\n%d", &num1, &num2);
  if (num1 < num2)
  {
    aux = num1;
    num1 = num2;
    num2 = aux;
  }
  while (num1 >= num2)
  {
    nao = 0;
    checknum = num1;
    if (num1 == 1)
    {
      break;
    }
    for (teste = 2; teste < (checknum / 2) + 1; teste ++)
    {
      if (checknum % teste == 0)
      {
        nao ++;
        break;
      }
    }
    if (nao == 0)
    {
      printf("%d\n", checknum);
    }
    num1 --;
  }
  return(0);
}
