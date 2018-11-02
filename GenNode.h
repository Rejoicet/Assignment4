#include <iostream>

using namespace std;

template <typename T>
class GenDlinkedlist;     //forward declaring the class

template <class T>
class GenQueue;

template <typename T>
class GenNode {
public:
  GenNode();
  GenNode(int key);
  ~GenNode();

private:
  T elem;
  GenNode<T> *prev;
  GenNode<T> *next;

  friend class GenDlinkedlist<T>;
  friend class GenQueue<T>;
  friend class Simulate;
};

template <class T>
GenNode<T>::GenNode()
{
  prev = NULL;
  next = NULL;
}

template <class T>
GenNode<T>::GenNode(int key)
{
  elem = key;
  prev = NULL;
  next = NULL;
}

template <class T>
GenNode<T>::~GenNode() {}
