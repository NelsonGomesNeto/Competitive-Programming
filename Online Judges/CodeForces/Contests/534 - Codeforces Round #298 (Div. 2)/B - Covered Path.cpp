#include <bits/stdc++.h>

int main()
{
  int v1, v2, t, d; scanf("%d %d %d %d", &v1, &v2, &t, &d);

  if (v1 > v2)
  {
    int aux = v1;
    v1 = v2;
    v2 = aux;
  }

  int dist = v1 + v2; t -= 2;
  while (t -- > 0)
  {
    if (v1 - (d * t) < v2)
      v1 += d;
    else
      v1 = v2 + (d * (t + 1));

    //printf("%d\n", v1);
    dist += v1;
  }

  printf("%d\n", dist);

  return(0);
}