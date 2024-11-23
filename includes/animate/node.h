#ifndef BARKESHLI__NODE_H__
#define BARKESHLI__NODE_H__

#include <iostream>
#include <iomanip>
using namespace std;


template <typename T>
struct node{
  
  node(const T& item= T(), node<T>* next = nullptr):_item(item), _next(next){
  }
  
  friend ostream& operator <<(ostream& outs, const node<T> n){
    outs<<"["<< n._item <<"]->";
    return outs;
  }

  T _item;
  node<T> *_next;
};

#endif // BARKESHLI__NODE_H__
