#include <bits/stdc++.h>

int main()
{
  int r, t = 0;
  while (scanf("%d", &r) && r != 0)
  {
    if (t) printf("\n");

    int aldo = 0, beto = 0, a, b;
    while (r -- > 0)
    {
      scanf("%d %d", &a, &b);
      aldo += a; beto += b;
    }

    printf("Teste %d\n%s\n", ++ t, aldo > beto ? "Aldo" : "Beto");
  }
  return(0);
}