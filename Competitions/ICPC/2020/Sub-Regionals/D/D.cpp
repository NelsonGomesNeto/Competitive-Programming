#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n; lli m, k;
const lli mod = 1e9 + 7;

void fastReadInt(lli &x)
{
  bool neg = false;
  int c = ' ';
  x = 0;
  while (c != '-' && (c < '0' || c > '9'))
    c = getchar();
 
  if (c == '-')
    neg = true, c = getchar();
 
  for ( ; (c > 47 && c < 58); c = getchar())
    x = (x<<1) + (x<<3) + c - 48;
  if (neg)
    x *=-1;
}

lli a[maxN], b[maxN];
vector<lli> da, db, ndb;
bool validShifts[maxN];

/*
  We need to find efficient (<= n*lg) ways to:
    1 - Find the valid shifts
    2 - Count the number of ways to apply k movements that end in a valid position

  1: Notice that in a valid shift, the sum is modularly constant
    So, if a[i + 1] = a[i] + 3 then b[i + 1] = b[i] - 3
    Since (a[i + 1] + b[i + 1]) % m == (a[i] + b[i]) % m

    Let's define "da" as da[i] = ((a[(i + 1) % n] - a[i]) % m + m) % m and "db" with "b"
    In a valid shift "s": da[i] == (-db[(i + s) % n] + m) % m

    We can find the valid shifts, using KMP (yes, the string algorithm to find substrings)
      Make db[i] = (-db[i] + m) % m
      Create a string: "db" + "db"
      Run KMP with "da" as a substring

  2: It only matters wheter you're on position 0 or not (because it's the initial position)
    if at 0:
      You can always go to n - 1 positions
    if not at 0:
      You can go to 0 or to n - 2 positions

    So you have the following recursive function:
      f(k, at 0) = (n - 1) * f(k - 1, not at 0)
      f(k, not at 0) = f(k - 1, at 0) + (n - 2) * f(k - 1, not at 0)
    
    This is a linear recurrence, which can be converted to the following matrix:
      (    0     1)
      (n - 1 n - 2)
    Apply matrix exponentiation: DONE
*/

vector<int> prefixFunction(vector<lli> &str)
{
  vector<int> pi(str.size() + 1, 0);
  pi[0] = -1;
  for (int i = 0, j = -1; i < str.size();)
  {
    while (j >= 0 && str[i] != str[j]) j = pi[j];
    pi[++i] = ++j;
  }
  return pi;
}
vector<int> kmp(vector<lli> &str, vector<int> &pi, vector<lli> &subStr)
{
  vector<int> occurrences;
  for (int i = 0, j = 0; i < str.size();)
  {
    while (j >= 0 && str[i] != subStr[j]) j = pi[j];
    i++, j++;
    if (j == subStr.size())
    {
      occurrences.push_back(i - j);
      j = pi[j];
    }
  }
  return occurrences;
}

lli brute(int i = 0, int lastShift = 0)
{
  if (i == k)
    return validShifts[lastShift];

  lli ans = 0;
  for (int s = 0; s < n; s++)
    if (s != lastShift)
      ans += brute(i + 1, s);
  return ans;
}

lli brute2(int target, int kk, int i = 0)
{
  if (kk == 0) return i == target;

  // lli ans = 0;
  // if (i == 0)
  //   ans = (ans + (n - 1) * brute2(target, kk - 1, 1) % mod) % mod;
  // else
  //   ans = (ans + brute2(target, kk - 1, 0) + (n - 2) * brute2(target, kk - 1, 1) % mod) % mod;
  lli ans = 0;
  for (int j = 0; j < n; j++)
    if (j != i)
      ans = (ans + brute2(target, kk - 1, j)) % mod;
  return ans;
}

lli memo[2][maxN + 1];
lli waysToZero(bool onZero = true, int kk = k)
{
  if (kk == 0) return onZero;
  lli &ans = memo[onZero][kk];
  if (ans != -1) return ans;

  ans = 0;
  if (onZero)
    ans = (ans + (n - 1) * waysToZero(false, kk - 1) % mod) % mod;
  else
    ans = (ans + waysToZero(true, kk - 1) + (n - 2) * waysToZero(false, kk - 1) % mod) % mod;
  return ans;
}
//wayz[0][kk + 1] = (n - 1) * (wayz[0][kk] + (kk & 1 ? 1 : -1))

vector<vector<lli>> matrixModMult(vector<vector<lli>> &aa, vector<vector<lli>> &bb)
{
  vector<vector<lli>> ans(aa.size(), vector<lli>(bb[0].size(), 0));
  for (int i = 0; i < aa.size(); i++)
    for (int j = 0; j < bb[0].size(); j++)
      for (int kk = 0; kk < aa[0].size(); kk++)
        ans[i][j] = (ans[i][j] + aa[i][kk] * bb[kk][j] % mod) % mod;
  return ans;
}
vector<vector<lli>> matrixModPow(vector<vector<lli>> &mat, lli y)
{
  vector<vector<lli>> ans(mat.size(), vector<lli>(mat[0].size(), 0));
  for (int i = 0; i < mat.size(); i++) ans[i][i] = 1;
  vector<vector<lli>> x = mat;
  while (y)
  {
    if (y & 1LL) ans = matrixModMult(ans, x);
    x = matrixModMult(x, x), y >>= 1LL;
  }
  return ans;
}

int main()
{
  while (~scanf("%d %lld %lld", &n, &m, &k))
  {
    for (int i = 0; i < n; i++)
      fastReadInt(a[i]);
    for (int i = 0; i < n; i++)
      fastReadInt(b[i]);

    DEBUG {
      for (int s = 0; s < n; s++)
      {
        printf("shift: %d\n\t", s);
        set<int> rems;
        for (int i = 0; i < n; i++)
        {
          lli aa = a[i], bb = b[(i + s) % n];
          rems.insert((aa + bb) % m);
          printf("(%lld + %lld = %lld | %lld)%c", aa, bb, aa + bb, (aa + bb) % m, i < n - 1 ? ' ' : '\n');
        }
        printf("\t%s\n", rems.size() == 1 ? "YES" : "NO");
      }
    }

    da.resize(n), db.resize(n), ndb.resize(2*n - 1);
    for (int i = 0; i < n; i++)
    {
      da[i] = ((a[(i + 1) % n] - a[i]) % m + m) % m;
      db[i] = ((b[(i + 1) % n] - b[i]) % m + m) % m;

      ndb[i] = (-db[i] + m) % m;
      if (n + i < 2*n - 1) ndb[n + i] = ndb[i];
    }
    DEBUG {
      printf("ndb: ");
      for (int i = 0; i < 2*n - 1; i++) printf("%lld%c", ndb[i], i < 2*n - 1 - 1 ? ' ' : '\n');
      printf("da : ");
      for (int i = 0; i < n; i++) printf("%lld%c", da[i], i < n - 1 ? ' ' : '\n');
    }

    vector<int> pi = prefixFunction(ndb);
    vector<int> occurences = kmp(ndb, pi, da);
    DEBUG {
      printf("valid shifts: ");
      for (int i = 0; i < occurences.size(); i++)
        printf("%d%c", occurences[i], i < occurences.size() - 1 ? ' ' : '\n');
      if (occurences.empty()) printf("\n");
    }

    memset(validShifts, false, sizeof(validShifts));
    for (int s: occurences) validShifts[s] = true;

    vector<vector<lli>> base = {{0, 1}, {n - 1, n - 2}};
    DEBUG printf("{{%lld, %lld}, {%lld, %lld}}\n", base[0][0], base[0][1], base[1][0], base[1][1]);
    vector<vector<lli>> res = matrixModPow(base, k);
    DEBUG printf("{{%lld, %lld}, {%lld, %lld}}\n", res[0][0], res[0][1], res[1][0], res[1][1]);
    lli ans = validShifts[0] ? res[0][0] : 0;
    for (int i = 1; i < n; i++)
      if (validShifts[i])
        ans = (ans + res[0][1]) % mod;
    printf("%lld\n", ans);

    DEBUG {
      for (int kk = 0; kk <= 13; kk++)
      {
        printf("k = %2d: ", kk);
        for (int i = 0; i < n; i++)
          printf("%10lld%c", brute2(i, kk), i < n - 1 ? ' ' : '\n');
      }
    }
  }
  return 0;
}