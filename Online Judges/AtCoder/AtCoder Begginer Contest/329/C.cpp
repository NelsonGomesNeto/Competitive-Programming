#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 2e5;
int n;
char s[kMaxN + 1];

int main() {
  while (~scanf("%d", &n)) {
    scanf(" %s", s);

    set<pair<char, int>> ans;
    for (int i = 0; i < n; ++i) {
      int j = i, cnt = 1;
      ans.insert({s[i], cnt});
      while (j + 1 < n && s[j + 1] == s[i]) {
        ++j, ++cnt;
        ans.insert({s[i], cnt});
      }

      i = j;
    }
    printf("%d\n", (int)ans.size());
  }
  return 0;
}
