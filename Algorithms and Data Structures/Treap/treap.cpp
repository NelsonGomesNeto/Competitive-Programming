#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int randPriority() { return rand() * 65536 + rand(); }
struct Treap
{
  int key, priority, size = 1;
  Treap *l = NULL, *r = NULL;
  Treap(int key, int priority = randPriority()) : key(key), priority(priority) { }
  void print(char end='\0') { printf("(%2d, %11d, %2d)%c", key, priority, size, end); }
};
Treap *treap;
void updateSize(Treap *&t)
{
  if (t)
    t->size = 1 + (t->l ? t->l->size : 0) + (t->r ? t->r->size : 0);
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
  else if (item->priority > t->priority)
  {
    split(t, item->key, item->l, item->r);
    t = item;
  }
  else insert(item->key < t->key ? t->l : t->r, item);
  updateSize(t);
}
void merge(Treap *&t, Treap *l, Treap *r)
{
  if (!l || !r) t = l ? l : r;
  else if (l->priority > r->priority) merge(l->r, l->r, r), t = l;
  else merge(r->l, l, r->l), t = r;
}
void erase(Treap *&t, int key)
{
  if (t->key == key) merge(t, t->l, t->r);
  else erase(key < t->key ? t->l : t->r, key);
  updateSize(t);
}
Treap* find(Treap *&t, int key)
{
  if (!t) return NULL;
  if (t->key == key) return t;
  return find(key < t->key ? t->l : t->r, key);
}
Treap* findByIndex(Treap *&t, int index, int before = 0) // be sure not to call this function when index >= t->size
{
  int leftSize = t->l ? t->l->size : 0;
  if (index == before + leftSize) return t;
  if (t->l && index < before + leftSize) return findByIndex(t->l, index, before);
  return findByIndex(t->r, index, before + leftSize + 1);
}
void print(Treap *t, int depth = 0)
{
  if (!t) return;
  print(t->r, depth + 1);
  for (int i = 0; i < depth; i++) printf("    ");
  t->print('\n');
  print(t->l, depth + 1);
}

int main()
{
  srand(time(NULL));

  for (int i = 0; i < 1e7; i++)
  {
    insert(treap, new Treap(i));
    DEBUG {
      print(treap);
      printf("-------------------\n");
    }
  }

  // for (int i = 0; i < 10; i++)
  //   findByIndex(treap, i)->print('\n');

  // for (int i = 0; i < 10; i++)
  // {
  //   erase(treap, i);
  //   DEBUG {
  //     print(treap);
  //     printf("-------------------\n");
  //   }
  // }
  return 0;
}