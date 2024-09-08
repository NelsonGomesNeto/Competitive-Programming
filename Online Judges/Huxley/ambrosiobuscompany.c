#include <stdio.h>

struct pessoa
{
  int ID, poltrona, idade;
  char data[20], de[99], para[99], horario[20], nome[99];
};

int main()
{
  int i = 0; float media = 0;
  struct pessoa p[9999];
  while (scanf("%d", &p[i].ID) && p[i].ID != -1)
  {
    getchar();
    scanf("%s", p[i].data);
    getchar();
    scanf("%[^\n]", p[i].de);
    getchar();
    scanf("%[^\n]", p[i].para);
    getchar();
    scanf("%s", p[i].horario);
    scanf("%d\n%d", &p[i].poltrona, &p[i].idade);
    getchar();
    scanf("%[^\n]", p[i].nome);
    media += p[i].idade;
    i ++;
  }
  media = (float) media / i;
  int j;
  for (j = 0; j < i; j ++)
  {
    if (p[j].idade > media && p[j].poltrona % 2 == 0)
    {
      printf("%s\n", p[j].nome);
    }
  }
  return(0);
}
