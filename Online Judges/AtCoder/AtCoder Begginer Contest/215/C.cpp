#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8; int n, k;
char ss[maxN + 1];

int main()
{
  while (~scanf(" %s %d", ss, &k))
  {
    string s = string(ss);
    sort(s.begin(), s.end());
    for (int i = 0; i < k - 1; i++) next_permutation(s.begin(), s.end());
    printf("%s\n", s.c_str());
  }
  return 0;
}