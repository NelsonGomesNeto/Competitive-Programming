#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* This probably can be solved using SegmentTrees
  There are only two cases for merging:
  Either you're merging same type brackets or not :)

  So you will either have a long chain of ([(
  Or you will have a long chain of (( or [[
    either way: you can pair them up by using operation 1
    so ((( will become just (
*/

const array<bool, 2> noneStartAt = {false, false};
array<bool, 2> posToStartAt(int i)
{
  array<bool, 2> a = noneStartAt;
  a[i] = true;
  return a;
}

struct Data
{
  // 0 - (), 1 - []
  bool balanced;
  array<bool, 2> startAt;
  int alterningSize;
  const string toString() const { return "(" + to_string(balanced) + " " + to_string(startAt[0]) + " " + to_string(startAt[1]) + " " + (alterningSize >= 0 ? " " : "") + to_string(alterningSize) + ")"; }
  Data operator+(const Data &other)
  {
    if (alterningSize == -1) return other;
    if (other.alterningSize == -1) return *this;

    if (balanced && other.balanced) return Data{true, noneStartAt, 0};
    else if (balanced) return other;
    else if (other.balanced) return *this;
    else
    {
      if (alterningSize == 0 && other.alterningSize == 0)
      {
        for (int i = 0; i < 2; i++)
          for (int j = 0; j < 2; j++)
            if (startAt[i] && other.startAt[j])
            {
              if (i == j) return Data{true, noneStartAt, 0};
              else return Data{false, posToStartAt(i), 1};
            }
      }
      else if (alterningSize == 0)
      {
        for (int i = 0; i < 2; i++)
          for (int j = 0; j < 2; j++)
            if (startAt[i] && other.startAt[j])
            {
              if (i == j) return Data{false, posToStartAt(j ^ 1), other.alterningSize - 1};
              else return Data{false, posToStartAt(i), other.alterningSize + 1};
            }
      }
      // else if (other.alterningSize == 0) // already handled by else hehe
      // {
      //   for (int i = 0; i < 2; i++)
      //     for (int j = 0; j < 2; j++)
      //       if (startAt[i] && other.startAt[j])
      //       {
      //         if ((i == j) ^ (alterningSize & 1)) return Data{false, startAt, alterningSize - 1};
      //         else return Data{false, startAt, alterningSize + 1};
      //       }
      // }
      else
      {
        for (int i = 0; i < 2; i++)
          for (int j = 0; j < 2; j++)
            if (startAt[i] && other.startAt[j])
            {
              if ((i == j) ^ (alterningSize & 1))
              {
                if (alterningSize == other.alterningSize) return Data{true, noneStartAt, 0};
                else if (alterningSize > other.alterningSize) return Data{false, startAt, alterningSize - other.alterningSize - 1};
                else
                {
                  int remSize = other.alterningSize - alterningSize - 1;
                  return Data{false, posToStartAt(j ^ (~alterningSize & 1)), remSize};
                }
              }
              else return Data{false, startAt, alterningSize + other.alterningSize + 1};
            }
      }
      assert(false);
      return {false, noneStartAt, -1};
    }
  }

};
const Data nil = Data{false, noneStartAt, -1};

// DON'T FORGET TO DEFINE THE NIL!!!
template<class T>
struct Segtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
  Segtree() { }
  Segtree(int size, T nil) : size(size), nil(nil)
  {
    data.resize(size);
    st.resize(4*size);
  }
  Segtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(4*size);
    build();
  }
  void build() { build(1, 0, size - 1); }
  T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
  void update(int pos, T value) { update(pos, value, 1, 0, size - 1); }
  void build(int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st[i] = data[lo];
      return;
    }
    int mid = (lo + hi) >> 1;
    build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
    DEBUG printf("merging [%2d : %2d] + [%2d : %2d]: %s -- %s\n", lo, mid, mid + 1, hi, st[2*i].toString().c_str(), st[2*i + 1].toString().c_str());
    st[i] = st[2*i] + st[2*i + 1];
  }
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    T l = query(qlo, qhi, 2*i, lo, mid);
    T r = query(qlo, qhi, 2*i + 1, mid + 1, hi);
    DEBUG printf("merging [%2d : %2d] + [%2d : %2d]: %s -- %s\n", lo, mid, mid + 1, hi, l.toString().c_str(), r.toString().c_str());
    return l + r;
  }
  void update(int pos, T &value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st[i] = data[lo] = value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

const int maxS = 1e6 + 1; int q;
char ss[maxS + 1];
char opo[256];
char charToPos[256];
string s;

int main()
{
  opo['('] = ')';
  opo[')'] = '(';
  opo['['] = ']';
  opo[']'] = '[';
  charToPos['('] = 0;
  charToPos[')'] = 0;
  charToPos['['] = 1;
  charToPos[']'] = 1;

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", ss);
    s = string(ss);

    segtree = Segtree<Data>(s.size(), nil);
    for (int i = 0; i < s.size(); i++)
      segtree.data[i] = Data{false, posToStartAt(charToPos[s[i]]), 0};
    segtree.build();
    DEBUG printf("-----------------\n");

    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
      int l, r; scanf("%d %d", &l, &r); l--, r--;
      Data curr = segtree.query(l, r);
      DEBUG {
        printf("\t%d %d - %s - %d %d %d %d\n", l, r, s.substr(l, r - l + 1).c_str(),
                                              curr.balanced, curr.startAt[0], curr.startAt[1], curr.alterningSize);
      }

      int x = 0;
      if (!curr.balanced)
      {
        x = (curr.alterningSize + 1) >> 1;
      }
      printf("%d\n", x);
    }
  }
  return 0;
}