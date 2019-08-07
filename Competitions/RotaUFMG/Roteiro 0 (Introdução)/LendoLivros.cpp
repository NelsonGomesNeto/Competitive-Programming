#include <bits/stdc++.h>

int main()
{
  double q, d, p;
  while (scanf("%lf", &q) && q != 0)
  {
    scanf("%lf %lf", &d, &p);

    double x2 = d / (1.0 - (q / p));
    double x1 = d / ((p / q) - 1.0);
    double pages = ((q * x2) + (p * x1)) / 2.0;
    if (ceil(pages) - pages <= 1e-5)
      pages = ceil(pages);
    else
      pages = floor(pages);
    printf("%.0lf pagina%s\n", pages, pages < 1.5 ? "\0" : "s");
  }
  return(0);
}
/*
{
  x2/x1 = p / q -> x1 = x2*(p/q)
  x2 - x1 = d

  x2 - x2*(p/q) = d
  x2*(1 - p/q) = d
  x2 = d / (1 - p/q)
}
*/