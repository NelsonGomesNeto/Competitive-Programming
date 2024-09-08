#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int test, run = 0; scanf("%d", &test);
  for (run = 1; run <= test; run ++)
  {
    getchar();
    int nums, ler;
    scanf("%d", &nums);
    char number[nums][9999];
    int quanti[nums];
    int i, j;
    for (ler = 0; ler < nums; ler ++)
    {
      quanti[nums] = 0;
      char aux[9999];
      int iM;
      for (iM = 0; iM < 7; iM ++)
      {
        scanf("%c", &aux[iM]);
        if (aux[iM] == '-' || aux[iM] == '\n' || aux[iM] == ' ')
        {
          iM --;
        }
      }
      for (i = 0, j = 0; i < strlen(aux); i ++)
      {
        if (aux[i] != '-')
        {
          if (aux[i] >= 'A' && aux[i] <= 'C')
          {
            number[ler][j] = '2';
          }
          else if (aux[i] >= 'D' && aux[i] <= 'F')
          {
            number[ler][j] = '3';
          }
          else if (aux[i] >= 'G' && aux[i] <= 'I')
          {
            number[ler][j] = '4';
          }
          else if (aux[i] >= 'J' && aux[i] <= 'L')
          {
            number[ler][j] = '5';
          }
          else if (aux[i] >= 'M' && aux[i] <= 'O')
          {
            number[ler][j] = '6';
          }
          else if (aux[i] >= 'P' && aux[i] <= 'S')
          {
            number[ler][j] = '7';
          }
          else if (aux[i] >= 'T' && aux[i] <= 'V')
          {
            number[ler][j] = '8';
          }
          else if (aux[i] >= 'W' && aux[i] <= 'Y')
          {
            number[ler][j] = '9';
          }
          else
          {
            number[ler][j] = aux[i];
          }
          j ++;
        }
      }
    }
    int o, b; char auxC[9999];
    int vezes, yep = 0;
    for (o = 0; o < nums;)
    {
      b = o; vezes = 0;
      //printf("%s~%d\n", number[o], o);
      while (strcmp(number[o], number[b]) == 0)
      {
        b ++;
        vezes ++;
        if (b >= nums)
        {
          break;
        }
      }
      if (vezes > 1)
      {
        yep ++;
        for (i = 0; i < 7; i ++)
        {
          printf("%c", number[o][i]);
          if (i == 2)
          {
            printf("-");
          }
        }
        printf(" %d\n", vezes);
      }
      if (vezes > 0)
      {
        o += vezes;
      }
      else
      {
        o ++;
      }
    }
    if (yep == 0)
    {
      printf("No duplicates.\n");
    }
    else
    {
      printf("\n");
    }
  }
  return(0);
}
