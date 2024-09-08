#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50;
int n;
int a[maxN];
char s[maxN + 1];
int letterToNum[maxN + 1];

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    fill(letterToNum, letterToNum+maxN+1, -1);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    scanf(" %s", s);

    bool can = true;
    for (int i = 0; i < n; ++i)
    {
      if (letterToNum[a[i]] == -1)
        letterToNum[a[i]] = s[i];
      can &= letterToNum[a[i]] == s[i];
    }
    printf("%s\n", can ? "YES" : "NO");
  }

  return 0;
}
