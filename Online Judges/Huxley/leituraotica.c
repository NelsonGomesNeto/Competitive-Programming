#include <stdio.h>

int main()
{
  int quest;
  while (scanf("%d", &quest) && quest != 0)
  {
    while (quest > 0)
    {
      int ans[5], ler, foi = 0, this; float media = 0;
      for (ler = 0; ler < 5; ler ++)
      {
        scanf("%d", &ans[ler]);
        media += ((float) ans[ler] / 5);
      }
      for (ler = 0; ler < 5; ler ++)
      {
        if (ans[ler] <= 127)
        {
          foi ++;
          this = ler;
        }
      }
      if (foi != 1)
      {
        printf("*\n");
      }
      else
      {
        printf("%c\n", (char) this + 65);
      }
      quest --;
    }
  }
  return(0);
}
