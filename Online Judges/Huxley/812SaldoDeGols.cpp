#include <bits/stdc++.h>

int main()
{
  int n, t = 0;
  while (scanf("%d", &n) && n)
  {
    if (t ++) printf("\n");
    int balance[n], a, b;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d %d", &a, &b);
      balance[i] = a - b;
    }

    int s = 0, lo, hi, sum = 0, maximum = -1e6, size = 0;
    for (int i = 0; i < n; i ++)
    {
      sum += balance[i];
      if (sum < 0) sum = 0, s = i + 1;
      if (sum > maximum || (sum >= maximum && (i - s + 1) > size))
        maximum = sum, size = (i - s + 1), lo = s, hi = i;
    }

    printf("Teste %d\n", t);
    if (maximum <= 0) printf("nenhum\n");
    else printf("%d %d\n", lo + 1, hi + 1);
  }
  return(0);
}
