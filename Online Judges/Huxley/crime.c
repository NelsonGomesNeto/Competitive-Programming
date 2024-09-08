#include <stdio.h>

int main()
{
  char quest[10]; int level = 0;
  printf("Telefonou para a vitima?\n");
  scanf("%s", quest);
  level += quest[0] == 'T' ? 1 : 0;
  printf("Esteve no local do crime?\n");
  scanf("%s", quest);
  level += quest[0] == 'T' ? 1 : 0;
  printf("Mora perto da vitima?\n");
  scanf("%s", quest);
  level += quest[0] == 'T' ? 1 : 0;
  printf("Devia para a vitima?\n");
  scanf("%s", quest);
  level += quest[0] == 'T' ? 1 : 0;
  printf("Ja trabalhou com a vitima?\n");
  scanf("%s", quest);
  level += quest[0] == 'T' ? 1 : 0;
  if (level < 2)
  {
    printf("Inocente\n");
  }
  else if (level == 2)
  {
    printf("Suspeita\n");
  }
  else if (level <= 4)
  {
    printf("Cumplice\n");
  }
  else
  {
    printf("Assassino\n");
  }
  return(0);
}
