#include <stdio.h>
#include <string.h>

int main()
{
  char num[99]; int printar, comeco, de, ate;
  while (scanf("%s", num) && strcmp(num,"0") != 0)
  {
    comeco = 0;
    for (printar = 0; printar < strlen(num); printar ++)
    {
      if (num[printar] != '0' && comeco == 0)
      {
        de = printar;
        comeco ++;
      }
    }
    comeco = 0;
    for (printar = strlen(num) - 1; printar >= de; printar --)
    {
      printf("[%c]", num[printar]);
      comeco ++;
    }
    if (comeco == 0)
    {
      printf("[0]");
    }
    printf("\n");
  }
}
