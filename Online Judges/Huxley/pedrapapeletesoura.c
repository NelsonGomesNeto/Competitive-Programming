#include <stdio.h>
#include <string.h>

int main()
{
  int jogos, mig = 0, rit = 0; char miguel[20], rita[20];
  for (jogos = 0; jogos < 5; jogos ++)
  {
    scanf("%[^\n]", rita);
    getchar();
    scanf("%[^\n]", miguel);
    if (strcmp(rita,"pedra") == 0)
    {
      if (strcmp(miguel,"pedra") == 0)
      {
        jogos --;
      }
      else if (strcmp(miguel,"tesoura") == 0)
      {
        rit ++;
      }
      else
      {
        mig ++;
      }
    }
    else if (strcmp(rita,"tesoura") == 0)
    {
      if (strcmp(miguel,"tesoura") == 0)
      {
        jogos --;
      }
      else if (strcmp(miguel,"pedra") == 0)
      {
        mig ++;
      }
      else
      {
        rit ++;
      }
    }
    else
    {
      if (strcmp(miguel,"papel") == 0)
      {
        jogos --;
      }
      else if (strcmp(miguel,"pedra") == 0)
      {
        rit ++;
      }
      else
      {
        mig ++;
      }
    }
    getchar();
  }
  if (mig > rit)
  {
    printf("MIGUEL\n");
  }
  else
  {
    printf("MARIA\n");
  }
  return(0);
}
