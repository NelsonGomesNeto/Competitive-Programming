#include <stdio.h>
#include <string.h>

int main()
{
  int dic, frases;
  while (scanf("%d %d", &dic, &frases) && !(dic == 0 && frases == 0))
  {
    char base[dic][99999], traduz[dic][99999]; int ler;
    for (ler = 0; ler < dic; ler ++)
    {
      getchar(); scanf("%s - > %s", base[ler], traduz[ler]);
    }
    char frase[999999]; int out, check, let, posi, nao;
    while (frases > 0)
    {
      getchar(); scanf("%[^\n]", frase);
      for (out = 0; out < strlen(frase); out ++)
      {
        for (check = 0; check < dic; check ++)
        {
          nao = 0;
          posi = out;
          for (let = 0; let < strlen(base[check]); let ++, posi ++)
          {
            //printf("#%c#~#%c#\n", frase[posi], base[check][let]);
            if (frase[posi] != base[check][let])
            {
              nao ++;
              let = strlen(base[check]);
            }
          }
          if (nao == 0)
          {
            printf("%s", traduz[check]);
            out = posi - 1;
            check = dic;
          }
        }
        if (nao != 0)
        {
          printf("%c", frase[out]);
        }
      }
      printf("\n");
      frases --;
    }
  }
  return(0);
}
