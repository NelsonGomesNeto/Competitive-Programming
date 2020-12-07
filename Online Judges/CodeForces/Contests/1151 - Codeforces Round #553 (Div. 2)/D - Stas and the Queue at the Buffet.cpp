#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
struct Person
{
  lli a, b, ab;
  bool operator<(const Person &p) const { return(ab > p.ab); }
};
Person people[maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld %lld", &people[i].a, &people[i].b);
    people[i].ab = people[i].a - people[i].b;
  }
  sort(people, people+n);

  lli sum = 0;
  for (lli i = 0; i < n; i ++)
    sum += i * people[i].a + (n - 1 - i) * people[i].b;
  printf("%lld\n", sum);

  return(0);
}