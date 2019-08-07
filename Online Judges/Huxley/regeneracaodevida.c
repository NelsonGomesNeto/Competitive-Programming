#include <stdio.h>

int main()
{
  int ataques, ler, recover, HP = 100, ativa, Time = 0; scanf("%d", &ataques);
  int atk[ataques], tempo[ataques];
  for (ler = 0; ler < ataques; ler ++)
  {
    scanf("%d %d", &atk[ler], &tempo[ler]);
  }
  scanf("%d", &recover);
  for (ler = 0; ler < ataques; ler ++)
  {
    if (HP < 100)
    {
      for (ativa = Time; ativa < tempo[ler]; ativa ++)
      {
        if (HP < 100)
        {
          HP += recover;
        }
      }
    }
    HP -= atk[ler];
    Time = tempo[ler];
  }
  if (HP <= 0)
  {
    printf("Inimigo Morto\n");
  }
  else
  {
    printf("Inimigo Vivo\n");
  }
  return(0);
}
