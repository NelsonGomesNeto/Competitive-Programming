#include <stdio.h>
#include <string.h>

struct amigo
{
  int ID_amigo; float grau;
};

struct new
{
  int ID_new;
  float tempo; char noti[999];
};

int main()
{
  int feed; scanf("%d", &feed);
  int amigos, ler; scanf("%d", &amigos);
  struct amigo a[amigos];
  for (ler = 0; ler < amigos; ler ++)
  {
    scanf("%d %f", &a[ler].ID_amigo, &a[ler].grau);
  }
  int news; scanf("%d", &news);
  struct new n[news];
  for (ler = 0 ; ler < news; ler ++)
  {
    scanf("%d %f", &n[ler].ID_new, &n[ler].tempo);
    getchar();
    scanf("%[^\n]", n[ler].noti);
  }
  int o, b, aux, se, pO, pB; float auxF; char auxC[999];
  for (o = 0; o < news; o ++)
  {
    for (b = 0; b < news; b ++)
    {
      for (se = 0; se < amigos; se ++)
      {
        if (n[o].ID_new == a[se].ID_amigo)
        {
          pO = se;
        }
        if (n[b].ID_new == a[se].ID_amigo)
        {
          pB = se;
        }
      }
      if ((0.8 * a[pO].grau) + (0.2 * n[o].tempo) > (0.8 * a[pB].grau) + (0.2 * n[b].tempo))
      {
        aux = n[o].ID_new;
        n[o].ID_new = n[b].ID_new;
        n[b].ID_new = aux;

        auxF = n[o].tempo;
        n[o].tempo = n[b].tempo;
        n[b].tempo = auxF;

        strcpy(auxC, n[o].noti);
        strcpy(n[o].noti, n[b].noti);
        strcpy(n[b].noti, auxC);
      }
    }
  }
  for (ler = 0; ler < feed; ler ++)
  {
    printf("%d %s\n", n[ler].ID_new, n[ler].noti);
  }
  return(0);
}
