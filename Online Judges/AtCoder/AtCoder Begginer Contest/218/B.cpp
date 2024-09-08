#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int p[26];
  for (int i = 0; i < 26; i++)
    scanf("%d", &p[i]);
  for (int i = 0; i < 26; i++)
    printf("%c", 'a' + p[i] - 1);
  printf("\n");
  return 0;
}