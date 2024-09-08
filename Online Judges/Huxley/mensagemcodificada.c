#include <stdio.h>
#include <ctype.h>
#include <locale.h>

char decodificar(char letra)
{
  if (letra == '4')
    return('a');
  if (letra == '5')
    return('e');
  if (letra == '1')
    return('i');
  if (letra == '0')
    return('o');
  if (letra == '2')
    return('u');
  return(letra);
}

int main()
{
  setlocale(LC_ALL, "English");
  char texto; int maiusculo = 1;
  while (scanf("%c", &texto) != EOF)
  {
    texto = decodificar(texto);
    if (maiusculo == 1 && texto > 64)
    {
      texto = toupper(texto);
      maiusculo = 0;
    }
    if (texto == '.')
    {
      maiusculo = 1;
    }
    if (texto != -61)
    {
      printf("%c", texto);
    }
    else if (texto == -8910)
    {
      printf("%s", "�");
    }
  } printf("\n");
  return(0);
}
