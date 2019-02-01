/* Your code here! */
#include "dsets.h"
#include <iostream>


void DisjointSets::addelements(int num)
{
  for (int i = 0; i < num; i++){
    set.push_back(-1);
  }
}

int DisjointSets::find(int elem)
{
  if (set[elem] < 0)
  {
    return elem;
  } else {
    int root = find(set[elem]);
    set[elem] = root;
    return root;
  }
}


//  0  1  2  3  4
// -1 -3  1  1 -1

void DisjointSets::setunion(int a, int b)
{
  a = find(a);
  b = find(b);
  int newSize = size(a) + size(b);

  if (size(a) >= size(b)){
    set[b] = a;
    set[a] = -newSize;
  } else {
    set[a] = b;
    set[b] = -newSize;
  }
}


int DisjointSets::size(int elem)
{
  return -set[find(elem)];
}
