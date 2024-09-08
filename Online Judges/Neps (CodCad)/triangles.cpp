//Codigo de exemplo
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int square(int a)
{
  return(a * a);
}

int main()
{
  vector<int> a;
  int i, x;
  for (i = 0; i < 3; i ++)
  {
    scanf("%d", &x);
    a.push_back(x);
  }
  sort(a.begin(), a.end());

  if (a[0] + a[1] <= a[2])
    printf("n\n");
  else if (square(a[2]) < square(a[0]) + square(a[1]))
    printf("a\n");
  else if (square(a[2]) > square(a[0]) + square(a[1]))
    printf("o\n");
  else //if (square(a[2]) == square(a[0]) + square(a[1]))
    printf("r\n");

}
