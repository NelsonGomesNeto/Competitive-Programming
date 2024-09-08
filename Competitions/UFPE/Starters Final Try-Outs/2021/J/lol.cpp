#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  vector<int> a = {1, 2, 3};
  rotate(a.begin(), a.begin()+a.size()-1, a.end());
  printf("%d %d %d\n", a[0], a[1], a[2]);
  return 0;
}