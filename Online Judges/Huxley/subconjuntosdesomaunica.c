#include <stdio.h>

int main()
{
  int somas; scanf("%d", &somas);
  int num[somas], ler, total, posi, obs, nope = 0, all, tudo, twoOut, twoIn;
  for (ler = 0; ler < somas; ler ++)
  {
    scanf("%d", &num[ler]);
    if (num[ler] < 0)
    {
      printf("-1\n");
      return(0);
    }
  }
  for (ler = 0; ler < somas; ler ++)
  {
    for (posi = ler; posi < somas; posi ++)
    {
      if (num[ler] > num[posi])
      {
        all = num[ler];
        num[ler] = num[posi];
        num[posi] = all;
      }
    }
  }
  for (tudo = 0; tudo < somas; tudo ++)
  {
    for (twoOut = tudo + 1; twoOut < somas; twoOut ++)
    {
      for (all = twoOut + 1; all < somas; all ++)
      {
        nope = 0;
        total = num[tudo] + num[twoOut] + num[all];
        for (posi = 0; posi < somas; posi ++)
        {
          for (twoIn = posi + 1; twoIn < somas; twoIn ++)
          {
            for (ler = twoIn + 1; ler < somas; ler ++)
            {
              if (num[posi] + num[twoIn] + num[ler] == total)
              {
                //printf("####{%d,%d,%d} = %d\n", num[posi], num[twoIn], num[ler], total);
                nope ++;
                if (nope == 2)
                {
                  ler = somas; posi = somas; twoIn = somas;
                }
              }
            }
          }
        }
        if (nope <= 1)
        {
          printf("{%d,%d,%d} = %d\n", num[tudo], num[twoOut], num[all], total);
        }
      }
    }
  }
  return(0);
}
