#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

template<class T>
struct MinMaxStack
{
  stack<T> maxS, minS, s;
  void clear()
  {
    while (!s.empty()) s.pop();
    while (!maxS.empty()) maxS.pop();
    while (!minS.empty()) minS.pop();
  }
  void push(T x)
  {
    if (maxS.empty() || x >= maxS.top()) maxS.push(x);
    if (minS.empty() || x <= minS.top()) minS.push(x);
    s.push(x);
  }
  T max() { assert(!maxS.empty()); return maxS.top(); }
  T min() { assert(!minS.empty()); return minS.top(); }
  T top() { assert(!s.empty()); return s.top(); }
  void pop()
  {
    if (s.empty())
      return;
    if (s.top() == maxS.top()) maxS.pop();
    if (s.top() == minS.top()) minS.pop();
    s.pop();
  }
  size_t size() { return s.size(); }
  bool empty() { return s.empty(); }
};
MinMaxStack<lli> mms;

int main()
{
  int q;
  while (scanf("%d", &q) != EOF)
  {
    while (q--)
    {
      int op; scanf("%d", &op);

      if (op == 1)
      {
        lli x; scanf("%lld", &x);
        mms.push(x);
      }
      else if (op == 2)
        printf("top: %lld, max: %lld, min: %lld\n", mms.top(), mms.max(), mms.min());
      else
        mms.pop();
    }
  }
  return 0;
}