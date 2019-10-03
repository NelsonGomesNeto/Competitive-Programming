#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
  int n;
  scanf("%d", &n);
  
  int a, b, c, d, e;
  scanf("%d", &a);
  if (n >= 2)
    scanf("%d", &b);
  if (n >= 3)
    scanf("%d", &c);
  if (n >= 4)
    scanf("%d", &d);
  if (n >= 5)
    scanf("%d", &e);

  if (n >= 2 && a > b)
  {
    int aux = a;
    a = b;
    b = aux;
  }
  if (n >= 3 && a > c)
  {
    int aux = a;
    a = c;
    c = aux;
  }
  if (n >= 4 && a > d)
  {
    int aux = a;
    a = d;
    d = aux;
  }
  if (n >= 5 && a > e)
  {
    int aux = a;
    a = e;
    e = aux;
  }
  if (n >= 3 && b > c)
  {
    int aux = b;
    b = c;
    c = aux;
  }
  if (n >= 4 && b > d)
  {
    int aux = b;
    b = d;
    d = aux;
  }
  if (n >= 5 && b > e)
  {
    int aux = b;
    b = e;
    e = aux;
  }
  if (n >= 4 && c > d)
  {
    int aux = c;
    c = d;
    d = aux;
  }
  if (n >= 5 && c > e)
  {
    int aux = c;
    c = e;
    e = aux;
  }
  if (n >= 5 && d > e)
  {
    int aux = d;
    d = e;
    e = aux;
  }
  
  printf("%d", a);
  if (n >= 2)
    printf(" %d", b);
  if (n >= 3)
    printf(" %d", c);
  if (n >= 4)
    printf(" %d", d);
  if (n >= 5)
    printf(" %d", e);
  printf("\n");

  return 0;
}