#include <stdio.h>
#include <math.h>

int main()
{
  int tam, ler, min = 0, limit = 1, maior = 0, iMa, posi, quanti[20], ignorados = 0;
  scanf("%d", &tam);
  float num[tam + 10];
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%f", &num[ler]);
    if (num[ler] < 0 || num[ler] > 10)
    {
      ignorados ++;
    }
  }
  for (ler = 0; ler < 10; ler ++)
  {
    quanti[ler] = 0;
  }
  for (limit = 1, min = 0, posi = 0; limit <= 10; posi ++, limit ++, min ++)
  {
    for (ler = 0; ler < tam; ler ++)
    {
      if (num[ler] > min && num[ler] <= limit)
      {
        quanti[posi] ++;
      }
      if (min == 0 && num[ler] == 0)
      {
        quanti[posi] ++;
      }
    }
    if (maior < quanti[posi])
    {
      maior = quanti[posi];
      iMa = posi;
    }
  }
  for (ler = 0; ler < 10; ler ++)
  {
    quanti[ler] = (20 * quanti[ler]) / maior;
  }
  char histo[22][12];
  for (ler = 20; ler >= 0; ler --)
  {
    for (posi = 0; posi < 10; posi ++)
    {
      if(quanti[posi] > 0)
      {
        histo[ler][posi] = '*';
        quanti[posi] --;
      }
      else if (quanti[posi] == 0)
      {
        histo[ler][posi] = '_';
        quanti[posi] --;
      }
      else
      {
        histo[ler][posi] = ' ';
      }
    }
  }
  int espaco = 0, numero;
  printf("     ^\n");
  //printf("     |\n");
  for (ler = 0; ler <= 20; ler ++)
  {
    if ((ler - 1) % 5 == 0 && ler != 0)
    {
      /*if (maior * (((4 - (ler / 5)) / 4)) != 0)
      {
        espaco = (int) floor(log10((maior * (((4 - (ler / 5)) / 4))))) + 1;
      }
      else
      {
      }*/
      numero = (maior * ((4 - ((ler - 1) / 5))) / 4);
      espaco = 3;
      while (numero >= 10)
      {
        espaco --;
        numero /= 10;
      }
      while (espaco > 0)
      {
        printf(" ");
        espaco --;
      }
      printf("%d +", (maior * ((4 - ((ler - 1) / 5))) / 4));
    }
    else
    {
      printf("     |");
    }
    for (posi = 0; posi <= 10; posi ++)
    {
      if (posi < 10)
      {
        if (histo[ler][posi] == '*')
        {
          printf("%c|", histo[ler][posi]);
        }
        else if (histo[ler][posi + 1] != '*')
        {
          printf("%c ", histo[ler][posi]);
        }
        else
        {
          printf("%c|", histo[ler][posi]);
        }
      }
    }
    printf("\n");
  }
  printf("   0 +--------+---------+->\n");
  printf("    0.0      5.0      10.0\n");
  printf("Valores ignorados: %d\n", ignorados);
  return(0);
}
