#include <stdio.h>

int main()
{
  int fari, ovo, col;
  scanf("%d %d %d", &fari, &ovo, &col);
  fari /= 2; ovo /= 3; col /= 5;
  if (fari <= ovo && fari <= col)
  {
    printf("%d\n", fari);
  }
  else if (ovo <= fari && ovo <= col)
  {
    printf("%d\n", ovo);
  }
  else if (col <= fari && col <= ovo)
  {
    printf("%d\n", col);
  }
}
