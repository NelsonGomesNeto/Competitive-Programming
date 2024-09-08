#include <stdio.h>
#include <string.h>

int main()
{
  int frases, ler, check, tudo, testes = 0;
  while (scanf("%d", &frases) && frases != 0)
  {
    testes ++;
    char string[99999], letra, letraFim[126], auxC;
    int conta[126], aux;
    for (ler = 0; ler < 126; ler ++)
    {
      conta[ler] = 0;
    }
    for (ler = 0; ler < frases; ler ++)
    {
      getchar();
      scanf("%[^\n]", string);
      for (check = 0; check < strlen(string); check ++)
      {
        for (letra = 0; letra < 126; letra ++)
        {
          if (letra == toupper(string[check]))
          {
            conta[(int) letra] ++;
            letraFim[(int) (letra)] = (char) toupper(letra);
          }
        }
      }
    }
    for (ler = 0; ler < 126; ler ++)
    {
      for (check = ler; check < 126; check ++)
      {
        if (conta[ler] < conta[check])
        {
          aux = conta[ler];
          conta[ler] = conta[check];
          conta[check] = aux;
          /*if (conta[ler] == conta[check])
          {
          if (letraFim[letra] > letraFim[check])
          {
          printf("%c~~~%c\n", letraFim[letra], letraFim[check]);
          auxC = letraFim[ler];
          letraFim[ler] = letraFim[check];
          letraFim[check] = auxC;
        }
      }
      else
      {
    }*/
          auxC = letraFim[ler];
          letraFim[ler] = letraFim[check];
          letraFim[check] = auxC;
        }
      }
    }
    for (ler = 0; ler < 126; ler ++)
    {
      for (check = 0; check < 126; check ++)
      {
        if (conta[ler] == conta[check])
        {
          if (letraFim[ler] < letraFim[check])
          {
            //printf("%d to %d\n", conta[ler], conta[check]);
            auxC = letraFim[ler];
            letraFim[ler] = letraFim[check];
            letraFim[check] = auxC;
          }
        }
      }
    }
    printf("TESTE %d\n", testes);
    for (ler = 0; ler < 126; ler ++)
    {
      if (conta[ler] != 0 && letraFim[ler] >= 'A' && letraFim[ler] <= 'Z')
      {
        printf("%c %d\n", letraFim[ler], conta[ler]);
      }
    }
  }
  return(0);
}
