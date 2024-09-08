#include <stdio.h>

int main()
{
  int num[10];
  int check, conta = 0;
  for (check = 0; check < 10; check ++)
  {
    scanf("%d", &num[check]);
  }
  for (check = 0; check < 10; check ++)
  {
    //printf("%d\n", num[check] % (((num[9] / 10) + 1) * 10));
    if (num[9] == num[check])
    {
      conta ++;
    }
  }
  printf("O numero %d apareceu %d vezes\n", num[9], conta);
  return(0);
}
