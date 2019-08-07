#include <bits/stdc++.h>
using namespace std;

int calculate(int p, int t)
{
  return(max(3*p/10, p - p/250*t));
}

int main()
{
  int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);

  int misha = calculate(a, c);
  int vasya = calculate(b, d);

  if (misha == vasya) printf("Tie\n");
  else if (misha > vasya) printf("Misha\n");
  else printf("Vasya\n");

  return(0);
}