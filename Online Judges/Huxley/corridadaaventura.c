#include <stdio.h>

int main()
{
  int cam;
  scanf("%i", &cam);
  if (cam > 3)
  {
    printf("inválido\n");
  }
  else if (cam == 1)
  {
    scanf("%i", &cam);
    if (cam != 4)
    {
      printf("inválido\n");
    }
    else
    {
      scanf("%i", &cam);
      if (cam != 6)
      {
        printf("inválido\n");
      }
      else
      {
        printf("válido\n");
      }
    }
  }
  else if (cam == 2)
  {
    printf("válido\n");
    scanf("%i", &cam);
    if (cam == 2)
    {
      printf("válido\n");
      scanf("%i", &cam);
      if (cam == 2)
      {
        printf("válido\n");
      }
      else
      {
        printf("invalido\n");
      }
    }
    else
    {
      printf("inválido\n");
    }
  }
  else
  {
    scanf("%i", &cam);
    if (cam != 5)
    {
      printf("inválido\n");
    }
    else
    {
      scanf("%i", &cam);
      if (cam != 7)
      {
        printf("inválido\n");
      }
      else
      {
        scanf("%i", &cam);
        if (cam != 8)
        {
          printf("inválido\n");
        }
        else
        {
          printf("válido\n");
        }
      }
    }
  }
  return(0);
}
