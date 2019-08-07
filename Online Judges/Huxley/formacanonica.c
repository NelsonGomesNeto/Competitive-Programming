#include <stdio.h>
#include <string.h>

int main()
{
  int quantas;
  scanf("%d", &quantas);
  while (quantas > 0)
  {
    char string[999] = "\0", dic[999] = "\0";
    getchar();
    scanf("%[^\n]", string);
    dic[0] = string[0];
    int i, j, posi, dif;
    for (i = 0; i < strlen(string); i ++)
    {
      dif = 0;
      for (j = 0; j < strlen(dic); j ++)
      {
        if (dic[j] == string[i] && string[i] != ' ')
        {
          dif ++;
        }
      }
      if (dif == 0)
      {
        dic[j] = string[i];
      }
    }
    for (i = 0; i < strlen(string); i ++)
    {
      for (j = 0; j < strlen(dic); j ++)
      {
        if (string[i] == dic[j])
        {
          string[i] = j + 'a';
          break;
        }
      }
    }
    printf("%s\n", string);
    quantas --;
  }
  return(0);
}
