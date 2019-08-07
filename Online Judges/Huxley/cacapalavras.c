#include <stdio.h>
#include <string.h>
#include <math.h>

int comparacoes;

int binsearch(char a[][20], char word[20], int begin, int end)
{
  int i, mid = (begin + end) / 2;
  if (begin > end)
  {
    return(0);
  }
  for (i = 0; a[mid][i] != '\0' && word[i] != '\0'; i ++)
  {
    comparacoes ++;
    if (a[mid][i] != word[i])
    {
      break;
    }
  }
  if (a[mid][i] == '\0' && word[i] == '\0')
  {
    return(1);
  }
  else
  {
    if (a[mid][i] < word[i])//(strcmp(a[mid], word) < 0)
    {
      return(binsearch(a, word, mid + 1, end));
    }
    else //(a[mid][i] > word[i])
    {
      return(binsearch(a, word, begin, mid - 1));
    }
  }
}

int main()
{
  int tam, toSearch;
  scanf("%d %d", &tam, &toSearch);
  char array[tam][20], palavra[20]; int i;
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
    if (binsearch(array, palavra, 0, tam - 1))
    {
      printf("SIM %d\n", comparacoes);
    }
    else
    {
      printf("NAO %d\n", comparacoes);
    }
  }
  return(0);
}
