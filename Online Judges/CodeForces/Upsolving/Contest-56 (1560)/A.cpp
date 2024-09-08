#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  vector<int> seq;
  seq.push_back(0);
  while (seq.size() < 1010)
  {
    int n = seq.back() + 1;
    while (n % 3 == 0 || n % 10 == 3) n++;
    seq.push_back(n);
  }
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int k; scanf("%d", &k);
    printf("%d\n", seq[k]);
  }
  return 0;
}
