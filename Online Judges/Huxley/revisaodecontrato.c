#include <stdio.h>
#include <string.h>

int main()
{
  int revisar, pode; char rev, contrato[1000000];
  while (scanf("%c", &rev) && getchar() && scanf("%[^\n]", contrato) && !(rev == '0' && strcmp(contrato,"0") == 0))
  {
    pode = 0;
    for (revisar = 0; revisar < strlen(contrato); revisar ++)
    {
      if (contrato[revisar] == rev)
      {
        contrato[revisar] = '0';
      }
      if (contrato[revisar] != '0')
      {
        pode ++;
      }
      if (pode > 0)
      {
        if (contrato[revisar] != '0')
        {
          printf("%c", contrato[revisar]);
        }
      }
    }
    if (pode == 0)
    {
      printf("0");
    }
    printf("\n");
    getchar();
  }
  return(0);
}
