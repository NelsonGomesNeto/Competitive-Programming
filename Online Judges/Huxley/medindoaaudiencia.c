#include <stdio.h>

int main()
{
  float novela1, novela2, futebol, filme1, filme2, media;
  scanf("%f\n%f\n%f\n%f\n%f", &novela1, &filme1, &futebol, &novela2, &filme2);
  media = (novela1 + novela2 + futebol + filme1 + filme2) / 5;
  printf("%.2f\n", media);
  if (novela1 >= filme1 && novela1 >= filme2 && novela1 >= futebol
   || novela2 >= filme1 && novela2 >= filme2 && novela2 >= futebol)
  {
    printf("NOVELA\n");
  }
  else if (filme1 >= novela1 && filme1 >= novela2 && filme1 >= futebol
   || filme2 >= novela1 && filme2 >= novela2 && filme2 >= futebol)
  {
    printf("FILME\n");
  }
  else
  {
    printf("FUTEBOL\n");
  }
  return(0);
}
