#include <stdio.h>

int main()
{
  int recipes, minimum, questions, l, h;
  scanf("%d %d %d", &recipes, &minimum, &questions);
  int flag[200001], total[200001], i;
  for (i = 0; i < 200001; i ++)
    flag[i] = total[i] = 0;

  for (i = 0; i < recipes; i ++)
  {
    scanf("%d %d", &l, &h);
    flag[l] ++;
    flag[h + 1] --;
  }

  int actual = 0, valid = 0;
  for (i = 0; i < 200001; i ++)
  {
    actual += flag[i];
    if (actual >= minimum)
      valid ++;

    total[i] = valid;
  }

  for (i = 0; i < questions; i ++)
  {
    scanf("%d %d\n", &l, &h);

    printf("%d\n", total[h] - total[l - 1]);
  }

  return(0);
}
