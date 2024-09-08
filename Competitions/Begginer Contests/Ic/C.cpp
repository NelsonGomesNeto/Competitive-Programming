#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

bool comp(string a, string b)
{
  string x = a + b;
  string y = b + a;
  return(x > y);
}

int main()
{
  int nums, ler;
  while (scanf("%d", &nums) && nums != 0)
  {
    string num[nums];
    for (ler = 0; ler < nums; ler ++)
    {
      cin >> num[ler];
    }
    int o, b; char auxC;
    sort(num, num + nums, comp);
    for (ler = 0; ler < nums; ler ++)
    {
      cout << num[ler];
    }
    printf("\n");
  }
  return(0);
}
