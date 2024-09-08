#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


char win[3];

int check(int s[3], int i, int atual)
{
  int j;
  for (j = 0; j < i; j ++)
  {
    if (s[j] % 3 == atual % 3)
    {
      return(0);
    }
  }
  return(1);
}

void bt(int b[9], int s[3], long long int *soma, int i)
{
  if (i == 3)
  {
    int k; long long int aux = 0;
    for (k = 0; k < 9; k ++)
    {
      aux += b[k];
    } aux = aux - b[s[0]] - b[s[1]] - b[s[2]];
    //printf("%d %d %d\n", s[0], s[1], s[2]);
    if (aux < *soma)
    {
      *soma = aux;
      win[0] = s[0];
      win[1] = s[1];
      win[2] = s[2];
    }
    else if (aux == *soma)
    {
      int ler; char string[3], auxC[3];
      for (ler = 0; ler < 3; ler ++)
      {
        if (s[ler] % 3 == 0)
        {
          string[ler] = 'B';
        }
        else if (s[ler] % 3 == 1)
        {
          string[ler] = 'G';
        }
        else
        {
          string[ler] = 'C';
        }
      }
      for (ler = 0; ler < 3; ler ++)
      {
        if (win[ler] % 3 == 0)
        {
          auxC[ler] = 'B';
        }
        else if (win[ler] % 3 == 1)
        {
          auxC[ler] = 'G';
        }
        else
        {
          auxC[ler] = 'C';
        }
      }
      if (strcmp(string, auxC) < 0)
      {
        *soma = aux;
        win[0] = s[0];
        win[1] = s[1];
        win[2] = s[2];
      }
    }
    return;
  }
  int j;
  for (j = 0; j < 3; j ++)
  {
    if (check(s, i, j + (i * 3)) == 1)
    {
      s[i] = j + (i * 3);
      bt(b, s, &*soma, i + 1);
    }
  }
}

int main()
{
  int bin[9], ler, maior = 0, posi;
  while (scanf("%d", &bin[0]) != EOF)
  {
    for (ler = 1; ler < 9; ler ++)
    {
      scanf("%d", &bin[ler]);
    }
    int string[3];
    win[0] = 2; win[1] = 2; win[2] = 2;
    long long int soma = pow(2, 31);
    bt(bin, string, &soma, 0);
    char s[3];
    for (ler = 0; ler < 3; ler ++)
    {
      if (win[ler] % 3 == 0)
      {
        s[ler] = 'B';
      }
      else if (win[ler] % 3 == 1)
      {
        s[ler] = 'G';
      }
      else
      {
        s[ler] = 'C';
      }
    }
    printf("%c%c%c %Ld\n", s[0], s[1], s[2], soma);
  }
  return(0);
}
