#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli randPriority() { return rand() * 65536 + rand(); }
struct Treap
{
  lli key, priority, v, vSum, size = 1, index;
  Treap *l = NULL, *r = NULL;
  Treap(lli key, lli v, lli priority = randPriority()) : key(key), v(v), priority(priority)
  {
  }
  void print(char end='\0') { printf("(%2lld, %11lld, %2lld)%c", key, priority, size, end); }
};
Treap *treap;
void updateNode(Treap *&t)
{
  if (t)
  {
    t->size = 1 + (t->l ? t->l->size : 0) + (t->r ? t->r->size : 0);
    t->vSum = t->v + (t->l ? t->l->v : 0);
  }
}
void split(Treap *t, int key, Treap *&l, Treap *&r)
{
  if (!t) l = r = NULL;
  else if (key < t->key) split(t->l, key, l, t->l), r = t;
  else split(t->r, key, t->r, r), l = t;
}
void insert(Treap *&t, Treap *item)
{
  if (!t) t = item;
  else if (t->key == item->key);
  else if (item->priority > t->priority)
  {
    split(t, item->key, item->l, item->r);
    t = item;
  }
  else insert(item->key < t->key ? t->l : t->r, item);
  updateNode(t);
}
void merge(Treap *&t, Treap *l, Treap *r)
{
  if (!l || !r) t = l ? l : r;
  else if (l->priority > r->priority) merge(l->r, l->r, r), t = l;
  else merge(r->l, l, r->l), t = r;
}
void erase(Treap *&t, int key)
{
  if (t == NULL) return;
  if (t->key == key) merge(t, t->l, t->r);
  else erase(key < t->key ? t->l : t->r, key);
  updateNode(t);
}
void print(Treap *t, int depth = 0)
{
  if (!t) return;
  print(t->r, depth + 1);
  for (int i = 0; i < depth; i++) printf("    ");
  t->print('\n');
  print(t->l, depth + 1);
}
Treap* find(Treap *&t, int key, int before = 0, lli sum = 0)
{
  if (!t) return NULL;
  t->index = before + (t->l ? t->l->size : 0);
  t->vSum = t->v + sum + (t->l ? t->l->vSum : 0);
  if (t->key == key) return t;
  return find(key < t->key ? t->l : t->r, key, key < t->key ? before : t->index + 1, key < t->key ? sum : t->vSum);
}
Treap* findByIndex(Treap *&t, int index, int before = 0)
{
  int currentIndex = before + (t->l ? t->l->size : 0);
  if (index == currentIndex) return t;
  if (t->l && index < currentIndex) return findByIndex(t->l, index, before);
  return findByIndex(t->r, index, currentIndex + 1);
}

int main()
{
  int q; scanf("%d", &q);
  lli l = 0;
  while (q--)
  {
    lli a, v; scanf("%lld %lld", &a, &v);
    a ^= l, v ^= l;
    insert(treap, new Treap(a, v));
    Treap *t = find(treap, a);
    printf("%lld %lld %lld\n", a, v, t->vSum);
    Treap *lol = findByIndex(treap, treap->size - 1);
    l = find(treap, lol->key)->vSum;
  }
  return 0;
}