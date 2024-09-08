#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int *chamadaSetBugado = malloc(1000001 * sizeof(int));
  memset(chamadaSetBugado, 0, 1000001 * sizeof(int));
  int alunos, presentes = 0, ID; scanf("%d", &alunos);
  for (; alunos > 0; alunos --)
  {
    scanf("%d", &ID);
    if (chamadaSetBugado[ID] == 0)
    {
      presentes ++; chamadaSetBugado[ID] ++;
    }
  }
  printf("%d\n", presentes);
  //free(chamadaSetBugado);
  return(0);
}
