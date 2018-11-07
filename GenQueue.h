#include <iostream>

using namespace std;

template <class T>
class GenQueue {
public:
  GenQueue();
  ~GenQueue();
  unsigned int size() const;
  bool isEmpty() const;
  T front() const;
  T back () const;
  void enqueue (const T& e);
  void dequeue();
  void printList() const;
  void remove();

  GenDlinkedlist<T> dList;

private:
  int n;
  friend class Simulate;
};

template <class T>
GenQueue<T>::GenQueue()
{
  n = 0;
}

template <class T>
GenQueue<T>::~GenQueue() {}

template <class T>
unsigned int GenQueue<T>::size() const
{
  return n;
}

template <class T>
bool GenQueue<T>::isEmpty() const
{
  return (n == 0);
}

template <class T>
T GenQueue<T>::front() const
{
  dList.front();
}

template <class T>
T GenQueue<T>::back() const
{
  dList.back();
}

template <class T>
void GenQueue<T>::enqueue (const T& e)
{
  dList.addBack(e);
  ++n;
}

template <class T>
void GenQueue<T>::dequeue ()
{
  dList.removeFront();
  --n;
}

template <class T>
void GenQueue<T>::printList() const
{
  dList.printList();
}

template <class T>
void GenQueue<T>::remove()
{
  dList.removeBack();
}
