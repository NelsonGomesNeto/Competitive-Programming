#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b;
  while (scanf("%d %d", &a, &b) != EOF)
  {
    string aa = "", bb = "";
    for (int i = 0; i < a; i ++)
      bb += b + '0';
    for (int i = 0; i < b; i ++)
      aa += a + '0';
    printf("%s\n", min(aa, bb).c_str());
  }
  return 0;
}