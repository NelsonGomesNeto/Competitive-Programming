#include <stdio.h>
#include <string.h>
#include <math.h>

int comparacoes;

int binsearch(char a[][100], char word[100], int i, int begin, int end)
{
  int mid = ((begin + end) / 2);
  if (begin > end)
  {
    return(0);
  }
  while (a[mid][i] != '\0' && word[i] != '\0' && a[mid][i] == word[i])
  {
    comparacoes ++;
    i ++;
  }
  /*if (a[mid][i] != '\0' && word[i] != '\0' && a[mid][i] == word[i])
  {
    comparacoes ++;
    return(binsearch(a, word, i + 1, begin, end));
  }*/
  if (a[mid][i] == '\0' && word[i] == '\0')
  {
    return(1);
  }
  if (a[mid][i] < word[i])
  {
    comparacoes ++;
    return(binsearch(a, word, 0, mid + 1, end));
  }
  if (a[mid][i] > word[i])
  {
    comparacoes ++;
    return(binsearch(a, word, 0, begin, mid - 1));
  }
}

int main()
{
  int tam, toSearch;
  scanf("%d %d", &tam, &toSearch);
  char array[tam][100], palavra[100]; int i;
  for (i = 0; i < tam; i ++)
  {
    getchar();
    scanf("%s", array[i]);
  }
  for (i = 0; i < toSearch; i ++)
  {
    getchar();
    scanf("%s", palavra);
    comparacoes = 0;
    if (binsearch(array, palavra, 0, 0, tam - 1))
    {
      printf("SIM %d\n", comparacoes);
      //printf("SIM %d ~~ %s\n", comparacoes, palavra);
    }
    else
    {
      printf("NAO %d\n", comparacoes);
      //printf("NAO %d ~~ %s\n", comparacoes, palavra);
    }
  }
  return(0);
}
