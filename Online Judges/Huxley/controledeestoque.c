#include <stdio.h>

int main()
{
  int cod[99999], quanti[99999], ler = 0;
  while (scanf("%d", &cod[ler]) && cod[ler] != 9999)
  {
    scanf("%d", &quanti[ler]);
    ler ++;
  }
  int cli, prod, vez, search;
  while (scanf("%d", &cli) && cli != 9999)
  {
    scanf("%d %d", &prod, &vez);
    for (search = 0; search < ler; search ++)
    {
      if (prod == cod[search])
      {
        if (vez <= quanti[search])
        {
          quanti[search] -= vez;
          printf("OK\n");
        }
        else
        {
          printf("ESTOQUE INSUFICIENTE\n");
        }
        search = ler;
      }
    }
  }
  int fim;
  for (fim = 0; fim < ler; fim ++)
  {
    printf("%d %d\n", cod[fim], quanti[fim]);
  }
  return(0);
}
