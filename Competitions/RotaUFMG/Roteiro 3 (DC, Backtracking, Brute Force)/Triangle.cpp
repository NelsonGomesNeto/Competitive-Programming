#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

void calculateDistance(int x[], int y[], double d[])
{
  for (int i = 0, j = 1; i < 3; i ++, j ++)
  {
    j %= 3;
    d[i] = sqrt(pow(x[j] - x[i], 2) + pow(y[j] - y[i], 2));
    DEBUG printf("%lf%c", d[i], i < 3 - 1 ? ' ' : '\n');
  }
  sort(d, d+3);
}

int zeroDistance(double d[])
{
  for (int i = 0; i < 3; i ++)
    if (d[i] - 1e-6 <= 0 && d[i] + 1e-6 >= 0)
      return(1);
  return(0);
}

int isRight(int x[], int y[])
{
  double d[3]; calculateDistance(x, y, d);
  if (zeroDistance(d)) return(0);
  return(pow(d[2], 2) + 1e-6 >= pow(d[1], 2) + pow(d[0], 2) && pow(d[2], 2) - 1e-6 <= pow(d[1], 2) + pow(d[0], 2));
}

int isAlmost(int x[], int y[])
{
  double d[3];
  for (int i = 0; i < 3; i ++)
  {
    x[i] ++;
    if (isRight(x, y)) return(1);
    x[i] -= 2;
    if (isRight(x, y)) return(1);
    x[i] ++;

    y[i] ++;
    if (isRight(x, y)) return(1);
    y[i] -= 2;
    if (isRight(x, y)) return(1);
    y[i] ++;
  }
  return(0);
}

int main()
{
  int x[3], y[3];
  for (int i = 0; i < 3; i ++)
    scanf("%d %d", &x[i], &y[i]);

  if (isRight(x, y))
    printf("RIGHT\n");
  else if (isAlmost(x, y))
    printf("ALMOST\n");
  else
    printf("NEITHER\n");

  return(0);
}