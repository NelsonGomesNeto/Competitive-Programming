#include <bits/stdc++.h>
using namespace std;

int main()
{
  string a, b;
  cin >> a >> b;

  if (a.size() != b.size()) { printf("NO\n"); return(0); }
  else
  {
    int lo = 0, hi = a.size() - 1;
    while (lo < a.size() && a[lo] == b[lo]) lo ++;
    while (hi >= 0 && a[hi] == b[hi]) hi --;
    if (lo >= hi) printf("YES\n");
    else
    {
      string aa = "", bb = "";
      for (int i = lo; i <= hi; i ++) aa += a[i], bb += b[i];
      reverse(bb.begin(), bb.end());
      printf("%s\n", aa == bb ? "YES" : "NO");
    }
  }
  return(0);
}