#include <stdio.h>

struct voo
{
  int ID, livre;
};

int main()
{
  struct voo v[37];
  int ler;
  for (ler = 0; ler < 37; ler ++)
  {
    scanf("%d %d", &v[ler].ID, &v[ler].livre);
  }
  int ID, fly;
  while (scanf("%d", &ID) && ID != 9999)
  {
    scanf("%d", &fly);
    int nope = 0;
    for (ler = 0; ler < 37; ler ++)
    {
      if (fly == v[ler].ID)
      {
        if (v[ler].livre != 0)
        {
          nope ++;
          printf("%d\n", ID);
          (v[ler].livre) --;
        }
        break;
      }
    }
    if (nope == 0)
    {
      printf("INDISPONIVEL\n");
    }
  }
  return(0);
}
