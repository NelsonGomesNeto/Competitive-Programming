#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int test, run = 0; scanf("%d", &test);
  int nums, ler; char auxC[9999];
  for (run = 1; run <= test; run ++)
  {
    if (run > 1)
    {
      printf("\n");
    }
    scanf("%d", &nums);
    //printf("~~~pp~~~%d\n", nums);
    string number[nums + 1];
    int i;
    for (ler = 0; ler < nums; ler ++)
    {
      char aux[999999];
      int iM, j;
      getchar();
      scanf("%s", aux);
      for (iM = 0, j = 0; iM < strlen(aux); iM ++)
      {
        if ((aux[iM] >= '0' && aux[iM] <= '9') || (aux[iM] >= 'A' && aux[iM] <= 'Y' && aux[iM] != 'Q'))
        {
          aux[j] = aux[iM];
          j ++;
        }
      }
      //printf("%s\n", aux);
      for (i = 0; i < 7; i ++)
      {
        if (aux[i] >= 'A' && aux[i] <= 'C')
        {
          aux[i] = '2';
        }
        else if (aux[i] >= 'D' && aux[i] <= 'F')
        {
          aux[i] = '3';
        }
        else if (aux[i] >= 'G' && aux[i] <= 'I')
        {
          aux[i] = '4';
        }
        else if (aux[i] >= 'J' && aux[i] <= 'L')
        {
          aux[i] = '5';
        }
        else if (aux[i] >= 'M' && aux[i] <= 'O')
        {
          aux[i] = '6';
        }
        else if (aux[i] >= 'P' && aux[i] <= 'S')
        {
          aux[i] = '7';
        }
        else if (aux[i] >= 'T' && aux[i] <= 'V')
        {
          aux[i] = '8';
        }
        else if (aux[i] >= 'W' && aux[i] <= 'Y')
        {
          aux[i] = '9';
        }
      }
      aux[7] = '\0';
      number[ler] = aux;
      //cout << number[ler] << endl;
    }
    int o, b;
    sort(number, number + nums);
    int vezes = 0, yep = 0;
    for (o = 0; o < nums; o ++)
    {
      if (number[o] == number[o + 1])
      {
        vezes ++;
      }
      else
      {
        if (vezes > 0)
        {
          yep ++;
          for (i = 0; i < 7; i ++)
          {
            cout << number[o][i];
            if (i == 2)
            {
              printf("-");
            }
          }
          printf(" %d\n", vezes + 1);
        }
        vezes = 0;
      }
    }
    if (yep == 0)
    {
      printf("No duplicates.\n");
    }
  }
  return(0);
}
