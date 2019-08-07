#include <stdio.h>

int main()
{
  int number; scanf("%d", &number);
  int a, b, c, d;
  a = number % 10; // 137*9*
  number /= 10; // 1379 -> 137
  b = number % 10; // 13*7*
  number /= 10; // 137 -> 13
  c = number % 10; // 1*3*
  number /= 10; // 13 -> 1
  d = number % 10; // *1*

  if (a > b)
  {
    int aux = a;
    a = b;
    b = aux;
  } // a <= b
  if (a > c)
  {
    int aux = a;
    a = c;
    c = aux;
  } // a <= b && a <= c
  if (a > d)
  {
    int aux = a;
    a = d;
    d = aux;
  } // a <= b && a <= c && a <= d
  if (b > c)
  {
    int aux = b;
    b = c;
    c = aux;
  }
  if (b > d)
  {
    int aux = b;
    b = d;
    d = aux;
  }
  if (c > d)
  {
    int aux = c;
    c = d;
    d = aux;
  }

  // a <= b <= c <= d
  // printf("%d %d%d%d%d\n", number, a, b, c, d);
  printf("%d%d%d%d\n", a, b, c, d);
  return(0);
}