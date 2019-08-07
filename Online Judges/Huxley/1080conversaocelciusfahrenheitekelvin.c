#include <stdio.h>
#include <math.h>

void printBug(double n)
{
  if ((int) round(n * 100) % 10 == 0)
    printf("%.1lf\n", round(n * 10) / 10);
  else
    printf("%.2lf\n", round(n * 100) / 100);
}


double ftoc(double f)
{
  return(((f - 32) * 5) / 9);
}

double ctof(double c)
{
  return(32 + (c * 1.8));
}

double ktoc(double k)
{
  return(k - 273);
}

double ctok(double c)
{
  return(c + 273);
}

int main()
{
  double temperature;
  char command;

  scanf("%c\n%lf", &command, &temperature);

  if (command == 'C')
  {
    if (ctok(temperature) < 0)
    {
      printf("Valor de temperatura abaixo do minimo\n");
      return(0);
    }
    printBug(ctof(temperature)); printf(" F\n");
    printBug(ctok(temperature)); printf(" K\n");
  } else if (command == 'K')
  {
    if (temperature < 0)
    {
      printf("Valor de temperatura abaixo do minimo\n");
      return(0);
    }
    printBug(ktoc(temperature)); printf(" C\n");
    printBug(ctof(ktoc(temperature))); printf(" F\n");
  } else
  {
    if (ctok(ftoc(temperature)) < 0)
    {
      printf("Valor de temperatura abaixo do minimo\n");
      return(0);
    }
    printBug(ftoc(temperature)); printf(" C\n");
    printBug(ctok(ftoc(temperature))); printf(" K\n");
  }

  return(0);
}
