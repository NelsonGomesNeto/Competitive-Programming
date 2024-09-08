#include <stdio.h>

void search(int a[], int *posi, int pontos)
{
  while (a[*posi] != pontos)
  {
    *posi += 1;
  }
}

int main()
{
  int times[16], i, j;
  for (i = 0; i < 16; i ++)
  {
    times[i] = 0;
  }
  int a, b;
  for (i = 0; i < 16; i += 2) //Oitavas de final
  {
    scanf("%d %d", &a, &b);
    if (a > b)
    {
      times[i] ++;
    }
    else
    {
      times[i + 1] ++;
    }
  }
  for (j = 0, i = 0; j < 4; j ++) //Quartas de final
  {
    scanf("%d %d", &a, &b);
    if (a > b)
    {
      search(times, &i, 1);
      times[i] ++;
      search(times, &i, 1); i ++;
    }
    else
    {
      search(times, &i, 1); i ++;
      search(times, &i, 1);
      times[i] ++;
    }
  }
  for (j = 0, i = 0; j < 2; j ++) //Semi-final
  {
    scanf("%d %d", &a, &b);
    if (a > b)
    {
      search(times, &i, 2);
      times[i] ++;
      search(times, &i, 2); i ++;
    }
    else
    {
      search(times, &i, 2); i ++;
      search(times, &i, 2);
      times[i] ++;
    }
  }
  for (j = 0, i = 0; j < 1; j ++) //Final
  {
    scanf("%d %d", &a, &b);
    if (a > b)
    {
      search(times, &i, 3);
      times[i] ++;
      search(times, &i, 3); i ++;
    }
    else
    {
      search(times, &i, 3); i ++;
      search(times, &i, 3);
      times[i] ++;
    }
  }
  i = 0;
  search(times, &i, 4);
  printf("%c\n", (char) i + 'A');
  return(0);
}
