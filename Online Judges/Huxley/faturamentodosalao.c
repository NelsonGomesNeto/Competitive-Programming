#include <stdio.h>
#include <string.h>

char sexo, tipo[20]; int convert, corte = 0, barba = 0, x = 0;
float fatura = 0;

int check()
{
  scanf("%s", &sexo);
  sexo = tolower(sexo);
  if (sexo == 'm')
  {
    x = 0;
    return(0);
  }
  else if (sexo == 'f')
  {
    x = 1;
    return(1);
  }
  else
  {
    x = 2;
    return(2);
  }
}

int main()
{
  while (check() != 2)
  {
    scanf("%s", &*tipo);
    for (convert = 0; convert < 20; convert ++)
    {
      tipo[convert] = tolower(tipo[convert]);
    }
    if (x == 0)
    {
      if (strcmp(tipo,"corte") == 0)
      {
        corte ++;
        fatura += 25;
      }
      else //if (strcmp(tipo,"barba") == 0)
      {
        barba ++;
        fatura += 15;
      }
    }
    else
    {
      if (strcmp(tipo,"corte") == 0)
      {
        fatura += 40;
      }
      else if (strcmp(tipo,"penteado") == 0)
      {
        fatura += 50;
      }
      else if (strcmp(tipo,"maquiagem") == 0)
      {
        fatura += 70;
      }
    }
  }
  if (barba > corte)
  {
    printf("BARBA\n%.2f\n", fatura);
  }
  else if (corte > barba)
  {
    printf("CORTE\n%.2f\n", fatura);
  }
  else
  {
    printf("AMBOS\n%.2f\n", fatura);
  }
  return(0);
}
//f corte = 40 || m corte = 25??
//barba = 15
//pentado = 50
