#include <stdio.h>

int main()
{
  int vitA, saldoA, golA, vitB, saldoB, golB;
  int convert = 0;
  char timeA[99];
  char timeB[99];
  scanf("%s\n%i\n%i\n%i", timeA, &vitA, &saldoA, &golA);
  scanf("%s\n%i\n%i\n%i", timeB, &vitB, &saldoB, &golB);

  while (convert <= 99)
  {
    timeA[convert] = tolower(timeA[convert]);
    convert ++;
  }
  convert = 0;
  while (convert <= 99)
  {
    timeB[convert] = tolower(timeB[convert]);
    convert ++;
  }

  if (vitA > vitB)
  {
    printf("%s\n", timeA);
  }
  else if (vitB > vitA)
  {
    printf("%s\n", timeB);
  }
  else
  {
    if (saldoA > saldoB)
    {
      printf("%s\n", timeA);
    }
    else if (saldoB > saldoA)
    {
      printf("%s\n", timeB);
    }
    else
    {
      if (golA > golB)
      {
        printf("%s\n", timeA);
      }
      else if (golB > golA)
      {
        printf("%s\n", timeB);
      }
      else
      {
        printf("EMPATE\n");
      }
    }
  }
}
