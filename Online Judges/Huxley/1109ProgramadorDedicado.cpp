#include <bits/stdc++.h>

void printDay(int day)
{
  if (day == 0) printf("DIA QUE MAIS PRODUZIU: NENHUM\n");
  if (day == 1) printf("DIA QUE MAIS PRODUZIU: DOMINGO\n");
  if (day == 2) printf("DIA QUE MAIS PRODUZIU: SEGUNDA\n");
  if (day == 3) printf("DIA QUE MAIS PRODUZIU: TERCA\n");
  if (day == 4) printf("DIA QUE MAIS PRODUZIU: QUARTA\n");
  if (day == 5) printf("DIA QUE MAIS PRODUZIU: QUINTA\n");
  if (day == 6) printf("DIA QUE MAIS PRODUZIU: SEXTA\n");
  if (day == 7) printf("DIA QUE MAIS PRODUZIU: SABADO\n");
}

int main()
{
  int programs, lines, best = 0, day = 0, mp = 0, ml = 0;
  for (int i = 0; i < 7; i ++)
  {
    scanf("%d %d\n", &programs, &lines);
    if (programs >= 5) mp ++;
    if (lines >= 100) ml ++;
    if (lines >= best)
    {
      day = i + 1;
      best = lines;
    }
  } if (best == 0) day = 0;

  printf("QUANTIDADE DE DIAS QUE ATINGIU MEDIA DE PROGRAMAS: %d\n", mp);
  printf("QUANTIDADE DE DIAS QUE ATINGIU MEDIA DE LINHAS: %d\n", ml);
  printDay(day);
  return(0);
}