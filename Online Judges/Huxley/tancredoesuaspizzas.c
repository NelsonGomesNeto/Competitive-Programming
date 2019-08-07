#include <stdio.h>
#include <string.h>

int main()
{
  int tests, run = 0; scanf("%d", &tests);
  while (tests > 0)
  {
    //printf("Punding\n");
    if (run > 0)
    {
      printf("\n");
    } run ++;
    int pizzas; scanf("%d", &pizzas);
    char pizza[pizzas][50], string[10010];
    int ler, p;
    for (ler = 0; ler < pizzas; ler ++)
    {
      getchar();
      scanf("%[^\n]", pizza[ler]);
    }
    getchar();
    scanf("%[^\n]", string);
    int i, j;
    for (j = 0; j < pizzas; j ++)
    {
      p = 0;
      for (i = 0; i < strlen(pizza[j]);)
      {
        int aux = 0;
        for (ler = 0; ler < strlen(string); ler ++)
        {
          if (pizza[j][i] == string[ler])
          {
            string[ler] = '|';
            i ++; aux ++;
          }
          if (i == strlen(pizza[j]))
          {
            ler = 0; p ++; i = 0;
          }
        }
        if (aux == 0)
        {
          break;
        }
      }
      printf("%d\n", p);
    }
    tests --;
  }
  return(0);
}
