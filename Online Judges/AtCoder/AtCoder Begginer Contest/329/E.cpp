#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 2e5;
int n, m;
int maximum_stamp;
string s, t;
set<string> stamps, pref, suf;

char ss[kMaxN + 1];
string ReadString() {
  scanf(" %s", ss);
  return string(ss);
}

int memo[kMaxN];
int Solve(int i = 0) {
  DEBUG printf("\t%d\n", i);
  if (i >= n) {
    return true;
  }
  int& ans = memo[i];
  if (ans != -1) {
    return ans;
  }
  ans = false;

  string curr;
  int j = 0;
  do {
    curr.push_back(s[i + j]);
    bool consider_pref = false, consider_suf = false;
    if (n - i > m) {
      consider_pref = true;
    }
    if (i + 1 > m) {
      consider_suf = true;
    }

    bool found = (consider_pref && pref.count(curr)) || (consider_suf && suf.count(curr)) || (curr == t);
    DEBUG printf("\t\t%d %d - %s | %d %d | %d\n", i, j, curr.c_str(), consider_pref, consider_suf, found);

    if (found) {
      ans = Solve(i + curr.size());
      if (ans) return ans;
    }
    // if (stamps.count(curr)) {
    //   ans = Solve(i + curr.size());
    //   if (ans) return ans;
    // }
    // if (stamps.count(curr)) {
    //   // if (i + curr.size() >= n) {
    //   //   ans = Solve(i + curr.size());
    //   //   if (ans) return ans;
    //   // } else {
    //   // }
    //   for (int k = 1; k <= curr.size(); ++k) {
    //     ans = Solve(i + k);
    //     if (ans) return ans;
    //   }
    // }
    ++j;
  } while (i + j < n && curr.size() < maximum_stamp);

  return ans;
}

void AddAllPrefixesAndSuffixes(const string& tt) {
  string curr;
  for (char c : tt) {
    curr.push_back(c);
    stamps.insert(curr);
    pref.insert(curr);
  }
  while (curr.size()) {
    stamps.insert(curr);
    suf.insert(curr);
    curr.erase(0, 1);
  }
}

int main() {
  while (~scanf("%d %d", &n, &m)) {
    s = ReadString();
    t = ReadString();

    maximum_stamp = 0;
    stamps.clear(), pref.clear(), suf.clear();
    AddAllPrefixesAndSuffixes(t);
    for (int i = 1; i < t.size(); ++i) {
      AddAllPrefixesAndSuffixes(t.substr(0, i) + t);
      AddAllPrefixesAndSuffixes(t + t.substr(t.size() - i, i));
    }
    for (auto& stamp : stamps) {
      maximum_stamp = max(maximum_stamp, (int)stamp.size());
    }
    DEBUG {
      printf("\tprefixes:\n");
      for (string a : pref) {
        printf("%s\n", a.c_str());
      }
      printf("\tsuffixes:\n");
      for (string a : suf) {
        printf("%s\n", a.c_str());
      }
    }

    memset(memo, -1, sizeof(memo));
    int ans = Solve();
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;

}