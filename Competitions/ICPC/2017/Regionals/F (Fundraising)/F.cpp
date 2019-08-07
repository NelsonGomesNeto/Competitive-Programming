#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
#define lli long long int

/* Explanation:
max segtree + greedy (I didn't understand the BIT solution...)
remind we can only join a and b if:
  (a or b) is strictly prettier and richer than (a or b)
  or
  (a and b) are equally pretty and rich
First: compress every person that has (beauty and fortune) exactly equal
Second: compress fortunes, because the value won't matter, just the order of them
Third: sort people by beauty ascending and fortune descending
Then with a maximum segtree we can apply the following:
  for each person in people
    best = query the maximum we can achieve from (0 to (person.fortune - 1))
      (since it's ascending by beauty, all that best can be joined with now's person)
    update person.fortune with (best + person.donation)
      (since it's a max segtree, it will only update if it's actually bigger)
  ans = query the maximum we can achieve with the biggest fortune
  (see why fortune is descending? We need to ensure that we won't join people
  with the same beauty, so we first update with the ones with bigger fortunes and
  then update with the ones with smaller fortunes)
*/

lli segtree[(int) 4e5];
int pos; lli value;
lli f(lli a, lli b) { return(max(a, b)); }
void update(int lo, int hi, int i = 1)
{
  if (hi < pos || lo > pos) return;
  if (lo >= hi)
  {
    segtree[i] = f(segtree[i], value);
    return;
  }
  int mid = (lo + hi) >> 1;
  update(lo, mid, 2*i); update(mid + 1, hi, 2*i + 1);
  segtree[i] = f(segtree[2*i], segtree[2*i + 1]);
}
int qlo, qhi;
lli query(int lo, int hi, int i = 1)
{
  if (lo > qhi || hi < qlo) return(0);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(f(query(lo, mid, 2*i), query(mid + 1, hi, 2*i + 1)));
}

struct Person { lli beauty, fortune, donation; };
int comp(const Person &a, const Person &b)
{
  return(a.beauty < b.beauty || (a.beauty == b.beauty && a.fortune > b.fortune));
}

int main()
{
  memset(segtree, 0, sizeof(segtree));
  int n; scanf("%d", &n);
  Person p[n]; set<lli> f;
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld %lld %lld", &p[i].beauty, &p[i].fortune, &p[i].donation);
    f.insert(p[i].fortune);
  }
  map<lli, int> fortuneCompression;
  for (lli i: f) { int s = fortuneCompression.size() + 1; fortuneCompression[i] = s; }
  sort(p, p+n, comp); vector<Person> people;
  for (int i = 0; i < n; i ++)
  {
    Person newp = p[i]; newp.fortune = fortuneCompression[newp.fortune];
    while (i + 1 < n && p[i].beauty == p[i + 1].beauty && p[i].fortune == p[i + 1].fortune)
      newp.donation += p[++ i].donation;
    people.push_back(newp);
  }

  for (int i = 0; i < people.size(); i ++)
  {
    qlo = 0, qhi = people[i].fortune - 1;
    lli best = query(0, fortuneCompression.size());
    value = best + people[i].donation, pos = people[i].fortune;
    update(0, fortuneCompression.size());
  }
  qlo = 0, qhi = fortuneCompression.size();
  printf("%lld\n", query(0, fortuneCompression.size()));
  return(0);
}
