#include <stdio.h>

int main()
{
  double prodM[2][12], total[2][2], preco[2][2]; int ler;
  total[0][0] = 0; total[0][1] = 0; total[1][0] = 0; total[1][1] = 0;
  for (ler = 0; ler < 12; ler ++)
  {
    scanf("%lf%lf", &prodM[0][ler], &prodM[1][ler]);
  }
  scanf("%lf%lf%lf%lf", &preco[0][0], &preco[0][1], &preco[1][0], &preco[1][1]);
  for (ler = 0; ler < 12; ler ++)
  {
    printf("Motor[0], Mes[%d], custo=[%.2f], lucro=[%.2f]\n", ler + 1, prodM[0][ler] * preco[0][0], prodM[0][ler] * preco[0][1]);
    total[0][0] += (prodM[0][ler] * preco[0][0]);
    total[0][1] += (prodM[0][ler] * preco[0][1]);
  }
  for (ler = 0; ler < 12; ler ++)
  {
    printf("Motor[1], Mes[%d], custo=[%.2f], lucro=[%.2f]\n", ler + 1, prodM[1][ler] * preco[1][0], prodM[1][ler] * preco[1][1]);
    total[1][0] += (prodM[1][ler] * preco[1][0]);
    total[1][1] += (prodM[1][ler] * preco[1][1]);
  }
  printf("Motor[0], anual, custo=[%.2f], lucro=[%.2f]\n", total[0][0], total[0][1]);
  printf("Motor[1], anual, custo=[%.2f], lucro=[%.2f]\n", total[1][0], total[1][1]);
  return(0);
}
