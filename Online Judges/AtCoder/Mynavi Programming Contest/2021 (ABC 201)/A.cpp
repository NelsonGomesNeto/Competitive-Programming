#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  vector<int> a(3);
  for (int i = 0; i < a.size(); i++)
    scanf("%d", &a[i]);
  sort(a.begin(), a.end());
  bool can = false;
  do
  {
    if (a[2] - a[1] == a[1] - a[0])
    {
      can = true;
      break;
    }
  }
  while (next_permutation(a.begin(), a.end()));

  printf("%s\n", can ? "Yes" : "No");
  return 0;
}