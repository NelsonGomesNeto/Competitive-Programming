#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2, maxC1 = 1e2; int n;
char s[maxC1 + 1];
string codes = ".-";
vector<string> c;
string prohibitedPrefix;

void buildTree(string curr = "") {
  if (c.size() == n) return;
  if (curr.size() == 10) {
    if (curr != prohibitedPrefix)
      c.push_back(curr);
    return;
  }
  if (curr == prohibitedPrefix)
    return;

  for (char code : codes)
    buildTree(curr + code);
}

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase) {
    c.clear();
    scanf("%d", &n);
    scanf(" %s", s);
    c.push_back(string(s));
    prohibitedPrefix = c[0].substr(0, min((int)c[0].size(), 10));

    buildTree();

    printf("Case #%d:\n", testCase);
    for (int i = 1; i < n; ++i) {
      printf("%s\n", c[i].c_str());
    }
  }
  return 0;
}
