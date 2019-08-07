//Codigo de exemplo
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

void print(bool a)
{
  if (a)
    printf("S\n");
  else
    printf("N\n");
}

int main()
{
  vector<int> num;
  int n, sum = 0, i = 0;
  while (scanf("%1d", &n) != EOF)
  {
    num.push_back(n);
    if (i == 0)
    {
      sum += n;
      i = 1;
    }
    else
    {
      sum -= n;
      i = 0;
    }
  }

printf("%d\n", sum);
  print(sum % 11 == 0);
}
