#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Explanation:
First simulate to t = 100, this will guarantee that every monster
have found it's cycle (and answer, if you've already found the solution).
For every possible intersection: z:
  every monster will reach z at: a_i + b_i*t_i
  a_i = time to reach z for the first time
  b_i = cycle size
  t_i = the t_i-th time the i-th monster reached z

  We have to find the time in which:
  a_1 + b_1*t_1 = a_2 + b_2*t_2
  a_1 + b_1*t_1 = a_3 + b_3*t_3
  ...
  a_1 + b_1*t_1 = a_n + b_n*t_n
  This system can be crunched in a diophantine equation, which
  can be solved using extended_gcd, it will give us x and y, and
  we can calculate the periodicity of it, just run through a bunch
  of them and save the smallest valid.
  BE VERY CAREFULL WHEN CALCULATING x0, IT CAN *EASILY* OVERFLOW
  MULT_MOD WILL SAVE YOU

How to crunch that system into a diophantine equation:
l = lcm(b_2, b_3, ..., b_n)
Multiply each line by l / b_i, where i is given by the rightmost equation
We can now add all equations:
a_1*(l/b_2 + l/b_3 + ... l/b_n) + b_1*(l/b_2 + l/b_3 + ... l/b_n)*t_1
=
(a_2*l/b_2 + a_3*l/b_3 + ... + a_n*l/b_n) + l*(t_2 + t_3 + ... + t_n)
It doesn't matter what t_2, t_3, ..., t_n is, just what the sum means
therefore (t_2 + t_3 + ... + t_n) = y
t_1 = x
a_1*(l/b_2 + l/b_3 + ... l/b_n) - (a_2*l/b_2 + a_3*l/b_3 + ... + a_n*l/b_n) = k
b_1*(l/b_2 + l/b_3 + ... l/b_n) = g
This way we can rewrite that big equation as:
k + g*x = l*y, a diophantine equation
*/

const int maxB = 10, maxZ = 100; int b, z;
const lli inf = LLONG_MAX;
int monsters[maxB][maxZ + 1];
vector<int> cycles[maxB];
vector<int> intersections;

lli gcdExtended(lli aa, lli bb, lli *x, lli *y)
{
  if (aa == 0)
  {
    *x = 0, *y = 1;
    return(bb);
  }
  lli x1, y1;
  lli g = gcdExtended(bb % aa, aa, &x1, &y1);
  *x = y1 - (bb / aa) * x1, *y = x1;
  return(g);
}
lli gcd(lli aa, lli bb) { if (aa == 0) return(bb); return(gcd(bb % aa, aa)); }
lli lcm(lli aa, lli bb) { return((aa / gcd(aa, bb)) * bb); }

lli modMult(lli aa, lli bb, lli m)
{
  if (bb == 0) return(0);
  lli r = modMult(aa, bb >> 1, m);
  r = (r + r) % m;
  if (bb & 1) r = (r + aa) % m;
  return(r);
}

bool monstersInSamePlace()
{
  for (int i = 1; i < b; i ++)
    if (monsters[0][0] != monsters[i][0])
      return(false);
  return(true);
}

bool canEmulating()
{
  int t;
  for (t = 0; t < 100; t ++)
  {
    if (monstersInSamePlace())
    {
      printf("%d %d\n", monsters[0][0], t);
      return(true);
    }
    for (int i = 0; i < b; i ++) monsters[i][0] = monsters[i][monsters[i][0]];
  }
  return(false);
}

int main()
{
  scanf("%d %d", &b, &z);
  for (int i = 0; i < b; i ++)
    for (int j = 0; j <= z; j ++)
      scanf("%d", &monsters[i][j]);

  if (canEmulating()) return(0);

  lli t = inf; int zoo = 1;
  for (int i = 0; i < b; i ++)
  {
    cycles[i].push_back(monsters[i][0]);
    for (int j = monsters[i][monsters[i][0]]; j != cycles[i][0]; j = monsters[i][j])
      cycles[i].push_back(j);
  }

  int first = 0;
  for (int target: cycles[first])
  {
    bool hasInAll = true;
    for (int i = 0; i < b; i ++)
    {
      if (i == first) continue;
      bool has = false;
      for (int j: cycles[i])
        if (j == target)
          has = true;
      if (!has) hasInAll = false;
    }
    if (hasInAll) intersections.push_back(target);
  }

  for (int z: intersections)
  {
    int meetsIn[b]; lli eqa = 0, eqb = -1, meets = 0;
    for (int i = 0, k = 0; i < b; i ++, k = 0)
    {
      while (cycles[i][k] != z) k ++;
      meetsIn[i] = k;
      if (i == first) continue;
      eqb = eqb == -1 ? cycles[i].size() : lcm(eqb, cycles[i].size());
    }
    for (int i = 0; i < b; i ++)
    {
      if (i == first) continue;
      eqa += cycles[first].size() * (eqb / cycles[i].size());
      meets += (meetsIn[first] - meetsIn[i]) * (eqb / cycles[i].size());
    }

    lli x, y;
    lli g = gcdExtended(eqa, eqb, &x, &y);
    lli dx = eqb / g;
    lli x0 = modMult((x < 0 ? -1 : 1) * -meets / g, x < 0 ? -x : x, dx);
    for (int j = 0; j < 100; j ++)
    {
      lli tt = x0 + dx*j;
      lli timeToReach = (lli) cycles[first].size() * tt + meetsIn[first];
      if (timeToReach <= 0) continue;
      bool valid = true;
      for (int i = 0; i < b; i ++)
      {
        if (i == first) continue;
        if ((timeToReach - meetsIn[i]) % cycles[i].size() != 0)
          valid = false;
      }
      if (valid)
      {
        if (timeToReach + 100 < t)
          t = timeToReach + 100, zoo = z;
        break;
      }
    }
  }
  if (t == inf) printf("*\n");
  else printf("%d %lld\n", zoo, t);
  return(0);
}