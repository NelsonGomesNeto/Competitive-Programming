#include <stdio.h>
#include <string.h>

int main()
{
  char seq[999];
  while (scanf("%s", seq) && !(seq[0] == '0' && seq[1] == '\0'))
  {
    int begin = 0, auxI = 0, auxF = 0, end = 0, i, quanti = 0, best = 0;
    int tam = strlen(seq);
    for (i = 0; i < tam; i ++)
    {
      auxF ++;
      if (seq[i] == '0')
      {
        quanti ++;
      }
      else
      {
        if (quanti > best)
        {
          best = quanti;
          end = auxF - 2;
          begin = auxI;
        }
        auxI = i + 1;
        quanti = 0;
      }
      seq[i] = '\0';
    }
    if (quanti > best)
    {
      best = quanti;
      end = auxF;
      begin = auxI;
    }
    printf("%d %d\n", begin, end);
    getchar();
  }
  return(0);
}
