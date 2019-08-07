#include <stdio.h>

int main()
{
  int casos, repeat, check, winner; scanf("%d", &casos);
  int figurinha[casos], joao = 0, maria = 0, joaoWin = 0, mariaWin = 0;
  for (repeat = 0; repeat < casos; repeat ++)
  {
    scanf("%d", &figurinha[repeat]);
    if (figurinha[repeat] % 2 == 0)
    {
      maria ++;
    }
    else
    {
      joao ++;
    }
    if (repeat > 1)
    {
      for (check = 0; check < repeat; check ++)
      {
        //printf("%d ~ %d\n", figurinha[check], figurinha[repeat]);
        if (figurinha[check] == figurinha[repeat])
        {
          figurinha[repeat] = 0;
        }
      }
    }
    if (figurinha[repeat] % 2 == 0)
    {
      mariaWin += figurinha[repeat];
    }
    else
    {
      joaoWin += figurinha[repeat];
    }
  }
  if (joaoWin > mariaWin)
  {
    winner = joaoWin;
  }
  else
  {
    winner = mariaWin;
  }
  printf("%d\n%d\n%d\n", maria, joao, winner);
  return(0);
}
