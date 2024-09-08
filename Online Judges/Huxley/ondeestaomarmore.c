#include <stdio.h>

int main()
{
  int marmores, consul, run = 0, once;
  while (scanf("%d %d", &marmores, &consul) && !(marmores == 0 && consul == 0))
  {
    run ++; once = 0;
    printf("CASE# %d:\n", run);
    while (consul > 0)
    {
      int pedras[marmores + 10], ler, o, b, aux, search, at, found = 0;
      if (once == 0)
      {
        for (ler = 0; ler < marmores; ler ++)
        {
          scanf("%d", &pedras[ler]);
        }
        for (o = 0; o < marmores; o ++)
        {
          for (b = o; b < marmores; b ++)
          {
            if (pedras[o] > pedras[b])
            {
              aux = pedras[o];
              pedras[o] = pedras[b];
              pedras[b] = aux;
            }
          }
        }
        once ++;
      }
      scanf("%d", &search);
      for (o = 0; o < marmores; o ++)
      {
        if (pedras[o] == search)
        {
          at = o + 1; found ++;
          break;
        }
        if (pedras[o] > search)
        {
          break;
        }
      }
      if (found > 0)
      {
        printf("%d found at %d\n", search, at);
      }
      else
      {
        printf("%d not found\n", search);
      }
      consul --;
    }
  }
  return(0);
}
