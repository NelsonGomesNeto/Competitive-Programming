#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;
struct Person
{
  lli a, b;
  double successRate;
  int index;
  void read()
  {
    scanf("%lld %lld", &a, &b);
  }
  bool operator<(const Person& other) const
  {
    const lli ls = a * (other.a + other.b);
    const lli rs = other.a * (a + b);
    return ls > rs || (ls == rs && index < other.index);
  }
};
Person people[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
    {
      people[i].read();
      people[i].index = i;
    }

    sort(people, people+n);
    for (int i = 0; i < n; ++i)
      printf("%d%c", people[i].index + 1, i + 1 < n ? ' ' : '\n');
  }
  return 0;
}
