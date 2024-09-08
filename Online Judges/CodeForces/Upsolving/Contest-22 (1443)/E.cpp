#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  vector<int> a(6);
  for (int i = 0; i < 6; i++)
    a[i] = i;

  do
  {
    for (int i = 0; i < 6; i++)
      printf("%d%c", a[i], i < 5 ? ' ' : '\n');
  } while (next_permutation(a.begin(), a.end()));
  

  return 0;
}
