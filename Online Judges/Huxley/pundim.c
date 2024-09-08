#include <stdio.h>

typedef struct _node node_t;

int miau(node_t *node);

int main()
{
  return(0);
}

struct _node
{
  int miau;
};

int miau(node_t *node)
{
  int weee = node->miau;
  return(weee);
}
