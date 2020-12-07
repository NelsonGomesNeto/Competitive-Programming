#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
char students[maxN + 1];

bool changes()
{
  bool change = false;
  for (int i = n - 2; i >= 0; i --)
    if (students[i] == 'A' && students[i + 1] == 'P')
      change = true, students[i + 1] = 'A';
  return change;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
  {
    while (t --)
    {
      scanf("%d", &n);
      scanf(" %s", students);

      int ans = 0;
      while (changes())
        ans ++;
      printf("%d\n", ans);
    }
  }
  return 0;
}
