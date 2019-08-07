#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main()
{
  int nums, ler;
  while (scanf("%d", &nums) && nums != 0)
  {
    string num[nums];
    for (ler = 0; ler < nums; ler ++)
    {
      getchar();
      scanf("%s", num[ler]);
    }
    int o, b; char auxC;
    sort(num, num + nums);
  }
  return(0);
}
