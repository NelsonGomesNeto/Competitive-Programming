#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, m;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    int a[n], votes = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      votes += a[i];
    }
    int minimum = votes / (4 * m) + (votes % (4 * m) != 0);

    int valid = 0;
    for (int i = 0; i < n; i++)
      if (a[i] >= minimum)
        valid++;
    printf("%s\n", valid >= m ? "Yes" : "No");
  }
  return 0;
}