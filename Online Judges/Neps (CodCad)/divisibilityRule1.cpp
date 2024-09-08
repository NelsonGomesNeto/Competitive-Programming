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
  int n, sum = 0;
  while (scanf("%1d", &n) != EOF)
  {
    num.push_back(n);
    sum += n;
  }

  print(num[num.size() - 1] % 2 == 0);

  print(sum % 3 == 0);

  print(num[num.size() - 1] == 0 || num[num.size() - 1] == 5);
}
