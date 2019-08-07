#include <stdio.h>
#include <string.h>

int main()
{
  int testes, conta, repeat; scanf("%d", &testes);
  char string[266];
  while (testes > 0)
  {
    conta = 0;
    getchar();
    scanf("%[^\n]", string);
    for (repeat = 0; repeat < strlen(string); repeat ++)
    {
      string[repeat] = toupper(string[repeat]);
      if (string[repeat] == 'A' || string[repeat] == 'D')
      {
        conta ++;
      }
      if(string[repeat] == 'O' || string[repeat] == 'P')
      {
        conta ++;
      }
      if (string[repeat] == 'R'|| string[repeat] == 'Q')
      {
        conta++;
      }
      if (string[repeat] == 'B') { conta += 2; }
    }
    testes --;
    printf("%d\n", conta);
  }
  return(0);
}
