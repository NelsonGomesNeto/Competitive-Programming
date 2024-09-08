#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;
char ss[maxN + 1];
string s;

int findAns()
{
  int ans = -1;
  for (int i = n - 1; i >= 0; --i)
  {
    if (s[i] == '-')
    {
      int j = i;
      while (j - 1 >= 0 && s[j - 1] == 'o')
        --j;

      int l = i - j + 1;
      DEBUG printf("\t%d %d - %d\n", i, j, l);
      if (l > 1)
        ans = max(ans, l - 1);

      i = j;
    }
  }
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", ss);
    s = string(ss);

    int ans = findAns();
    reverse(s.begin(), s.end());
    ans = max(ans, findAns());
    
    printf("%d\n", ans);
  }
  return 0;
}
