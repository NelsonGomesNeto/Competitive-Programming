#include <stdio.h>

int main()
{
  int matricula, matriculamenor, divi = -1;
  float nota = -1, notamenor = 11, soma = 1, media;
  while (matricula != 999)
  {
    if (nota != -1)
    {
      scanf("%f", &nota);
    }
    soma += nota;
    if (nota < notamenor && nota != -1)
    {
      notamenor = nota;
      matriculamenor = matricula;
    }
    scanf("%i", &matricula);
    divi ++;
    nota++;
  }
  media = soma / divi;
  printf("%i\n%.2f\n", matriculamenor, media);
  return(0);
}
