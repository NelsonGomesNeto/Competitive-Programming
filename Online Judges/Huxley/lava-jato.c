#include <stdio.h>
#include <string.h>

int main()
{
  char carro[40], tipo[40], nivel[40];
  int convert, cliente, Nsocio = 0, brindes = 0; float total = 0;
  for (cliente = 0; cliente < 5; cliente ++)
  {
    scanf("%s", &*carro);
    getchar();
    scanf("%[^\n]", &*tipo);
    getchar();
    scanf("%[^\n]", &*nivel);
    for (convert = 0; convert < 40; convert ++)
    {
      carro[convert] = tolower(carro[convert]);
      tipo[convert] = tolower(tipo[convert]);
      nivel[convert] = tolower(nivel[convert]);
    }
    if (strcmp(carro,"pequeno") == 0)
    {
      if (strcmp(tipo,"sem cera") == 0)
      {
        if (strcmp(nivel,"socio") == 0 || strcmp(nivel,"sócio") == 0 || strcmp(nivel,"sÓcio") == 0)
        {
          total += 20;
          Nsocio ++;
        }
        else
        {
          total += 30;
        }
      }
      else
      {
        if (strcmp(nivel,"socio") == 0 || strcmp(nivel,"sócio") == 0 || strcmp(nivel,"sÓcio") == 0)
        {
          total += 30;
          Nsocio ++;
        }
        else
        {
          total += 40;
        }
        brindes ++;
      }
    }
    else
    {
      if (strcmp(tipo,"sem cera") == 0)
      {
        if (strcmp(nivel,"socio") == 0 || strcmp(nivel,"sócio") == 0 || strcmp(nivel,"sÓcio") == 0)
        {
          total += 40;
          Nsocio ++;
        }
        else
        {
          total += 50;
        }
      }
      else
      {
        if (strcmp(nivel,"socio") == 0 || strcmp(nivel,"sócio") == 0 || strcmp(nivel,"sÓcio") == 0)
        {
          total += 60;
          Nsocio ++;
        }
        else
        {
          total += 80;
        }
        brindes ++;
      }
    }
  }
  printf("%i\n%i\n%.2f\n", Nsocio, brindes, total);
  return(0);
}
