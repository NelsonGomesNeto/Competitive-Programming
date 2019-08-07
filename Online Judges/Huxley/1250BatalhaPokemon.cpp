#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  while (n --)
  {
    double v1, v2, d1, d2; scanf("%lf %lf %lf %lf", &v1, &v2, &d1, &d2);
    //printf("Clodes: %d %d; Bezaliel: %d %d\n", v1, d1, v2, d2);
    int turns = ceil(v1 / d2), winner = 0;
    //printf("%d turns\n", turns);

    while (turns -- && ceil(v1 / d2) < ceil(v2 / d1))
    {
      d1 += 50;
      v1 -= d2;
    }

    //printf("%lf %lf %d\n", v1 / d2, v2 / d1, turns);
    winner = ceil(v1 / d2) < ceil(v2 / d1);
    printf("%s\n", winner ? "Bezaliel" : "Clodes");
  }
  return(0);
}