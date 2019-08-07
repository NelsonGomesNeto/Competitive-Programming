#include <stdio.h>
#include <string.h>

int main()
{
  char linhas[300];
  while (scanf("%[^\n]", linhas) && linhas[0] != '*')
  {
    int i, abre = 0, run = 0, jump; char fim[300], *j = linhas;
    while (sscanf(j, "%s%n", fim, &jump) == 1)
    {
      //fim[0] = toupper(fim[0]);
      if (run > 0)
      {
        printf(" ");
      }
      for (i = 0; i < strlen(fim); i ++)
      {
        fim[i] = tolower(fim[i]);
      }
      if (!(strcmp(fim, "e")  == 0 || strcmp(fim, "da")  == 0 || strcmp(fim, "de")  == 0 || strcmp(fim, "di")  == 0 || strcmp(fim, "do")  == 0 || strcmp(fim, "du") == 0))
      {
        fim[0] = toupper(fim[0]);
      }
      j += jump;
      run ++;
      printf("%s", fim);
    }
    printf("\n");
    getchar();
  }
  return(0);
}
