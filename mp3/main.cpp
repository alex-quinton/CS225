#include "List.h"
#include <iostream>

int main() {
  List<int> mergetest1;
  mergetest1.insertBack(3);
  mergetest1.insertBack(7);
  List<int> mergetest2;
  mergetest2.insertBack(4);
  mergetest2.insertBack(6);
  mergetest1.mergeWith(mergetest2);
  mergetest1.print(std::cout);
  std::cout << std::endl;




  List<int> test1;
  test1.insertBack(7);
  test1.insertBack(3);
  test1.insertBack(6);
  test1.insertBack(4);
  test1.insertBack(1);
  test1.insertBack(2);
  test1.insertBack(8);
  test1.insertBack(5);

  test1.sort();
  test1.print(std::cout);
  std::cout << std::endl;

  return 0;
}
