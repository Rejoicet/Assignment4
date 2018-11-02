#include <iostream>

using namespace std;

template <typename T>
class GenQueue;         //forward declaring the class

template <typename T>
class GenDlinkedlist {
public:
  GenDlinkedlist();
  ~GenDlinkedlist();

  bool isEmpty() const;
  T front() const;
  T back() const;
  void addFront (const T& e);
  void addBack (const T& e);
  void removeFront();
  void removeBack();
  GenNode<T> *add (T key, const T& e); //insert new node before GenNode *node
  GenNode<T> *remove (T key);
  void printList () const;
  bool contains (T e);
  void reduce ();
  T sort (T c, T d, T& s, T& med);

private:
  GenNode<T> *header;
  GenNode<T> *trailer;
  T ns;

  friend class GenQueue<T>;
  friend class Simulate;
};

template <class T>
GenDlinkedlist<T>::GenDlinkedlist ()
{
  header = new GenNode<T>;
  trailer = new GenNode<T>;
  header -> next = trailer;
  trailer -> prev = header;
}

template <class T>
GenDlinkedlist<T>::~GenDlinkedlist() {}

template <class T>
bool GenDlinkedlist<T>::isEmpty() const
{
  return (header -> next == trailer);
}

template <class T>
T GenDlinkedlist<T>::front() const
{
  return header -> next -> elem;
}

template <class T>
T GenDlinkedlist<T>::back() const
{
  return trailer -> prev -> elem;
}

template <class T>
GenNode<T>* GenDlinkedlist<T>::add (T key, const T& e)
{
  GenNode<T> *node = new GenNode<T>;
  node = header -> next;

  while (node != trailer) {
    if (node -> elem == key) {
      GenNode<T> *curr = new GenNode<T>;
      curr -> elem = e;
      curr -> next = node;
      curr -> prev = node -> prev;
      node -> prev -> next = curr;
      node -> prev = curr;
      break;
    }
    else {
      node = node -> next;
    }

    if (node == trailer) {
      cout << "There is no node with element " << key << " in the linked list. Failed to add " << e << "." << endl;
    }
  }
}

template <class T>
void GenDlinkedlist<T>::addFront (const T& e)
{
  GenNode<T> *node = new GenNode<T>;
  node -> elem = e;
  node -> prev = header;
  node -> next = header -> next;
  header -> next -> prev = node;
  header -> next = node;
}

template <class T>
void GenDlinkedlist<T>::addBack (const T& e)
{
  GenNode<T> *node = new GenNode<T>;
  node -> elem = e;
  node -> prev = trailer -> prev;
  node -> next = trailer;
  trailer -> prev -> next = node;
  trailer -> prev = node;
}

template <class T>
GenNode<T> *GenDlinkedlist<T>::remove (T key)
{
  GenNode<T> *node = new GenNode<T>;
  node = header -> next;

  while (node != trailer) {
    if (node -> elem == key) {
      node -> prev -> next = node -> next;
      node -> next -> prev = node -> prev;
      node -> next = node -> prev = NULL;
      delete node;
      break;
    }
    else {
      node = node -> next;
    }

    if (node == trailer) {
      cout << "There is no node with element " << key << " in the linked list." << endl;
    }
  }
}

template <class T>
void GenDlinkedlist<T>::removeFront()
{
  if (isEmpty() == true) {
    cout << "This is an empty list! Failed to remove the front element." << endl;
  }
  else {
    remove (header -> next -> elem);
  }
}

template <class T>
void GenDlinkedlist<T>::removeBack()
{
  if (isEmpty() == true) {
    cout << "This is an empty list! Failed to remove the back element." << endl;
  }
  else {
    GenNode<T> *node = new GenNode<T>;
    node = trailer;
    node = node -> prev;
    node -> prev -> next = node -> next;
    node -> next -> prev = node -> prev;
    node -> next = node -> prev = NULL;
    delete node;
  }
}

template <class T>
void GenDlinkedlist<T>::printList() const
{
  GenNode<T> *curr = new GenNode<T>;
  curr = header;
  curr = curr -> next;

  while (curr != trailer) {
    cout << curr -> elem << endl;
    curr = curr -> next;
  }
}

template <class T>
bool GenDlinkedlist<T>::contains (T e)
{
  if (isEmpty() == true) {
    return false;
  }
  else {
    GenNode<T> *cur = new GenNode<T>;
    cur = header;
    cur = cur -> next;

    while (cur != trailer) {
      if (cur -> elem == e) {
        return true;
      }
      cur = cur -> next;
    }
  }

return false;
}

template <class T>
void GenDlinkedlist<T>::reduce ()
{
  GenNode<T> *current = new GenNode<T>;
  current = header;
  current = current -> next;

  while (current != trailer) {
    current -> elem = current -> elem - 1;
    current = current -> next;
  }
}

template <class T>
T GenDlinkedlist<T>::sort(T c, T d, T& s, T& med)
{
  if (isEmpty() == true) {
    addBack (c - d);
    s = s + (c-d);
    med = c-d;
    ++ns;
  }
  else {
    if ((c-d) > back() || (c-d) == back()) {
      addBack (c-d);
      s = s + (c-d);
      ++ns;
      if (ns % 2 == 0) {
        GenNode<T> *cursor = new GenNode<T>;
        cursor = header;
        cursor = cursor -> next;
        for (int i = 0; i < (ns/2); i++) {
          cursor = cursor -> next;
        }
        med = (cursor -> elem + cursor -> prev -> elem)/2;
      }
      else {
        GenNode<T> *cursor = new GenNode<T>;
        cursor = header;
        cursor = cursor -> next;
        int j = ns - 1;
        for (int i = 0; i < (j/2); i++) {
          cursor = cursor -> next;
        }
        med = cursor -> elem;
      }
    }
    else if ((c-d) < back()) {
      if ((c-d) < front() || (c-d) == front()) {
        addFront (c-d);
        s = s + (c-d);
        ++ns;
        if (ns % 2 == 0) {
          GenNode<T> *cursor = new GenNode<T>;
          cursor = header;
          cursor = cursor -> next;
          for (int i = 0; i < (ns/2); i++) {
            cursor = cursor -> next;
          }
          med = (cursor -> elem + cursor -> prev -> elem)/2;
        }
        else {
          GenNode<T> *cursor = new GenNode<T>;
          cursor = header;
          cursor = cursor -> next;
          ns = ns - 1;
          for (int i = 0; i < (ns/2); i++) {
            cursor = cursor -> next;
          }
          med = cursor -> elem;
        }
      }
      else {
        GenNode<T> *current = new GenNode<T>;
        current -> elem = c-d;
        GenNode<T> *cursor = new GenNode<T>;
        cursor = header;
        cursor = cursor -> next;
        cursor = cursor -> next;
        while (cursor != trailer) {
          if (current -> elem < cursor -> elem || current -> elem == cursor -> elem) {
            add (cursor -> elem, current -> elem);
            s = s + (c-d);
            ++ns;
            if (ns % 2 == 0) {
              GenNode<T> *cursor = new GenNode<T>;
              cursor = header;
              cursor = cursor -> next;
              for (int i = 0; i < (ns/2); i++) {
                cursor = cursor -> next;
              }
              med = (cursor -> elem + cursor -> prev -> elem)/2;
            }
            else {
              GenNode<T> *cursor = new GenNode<T>;
              cursor = header;
              cursor = cursor -> next;
              ns = ns - 1;
              for (int i = 0; i < (ns/2); i++) {
                cursor = cursor -> next;
              }
              med = cursor -> elem;
            }
            break;
          }
          cursor = cursor -> next;
        }
      }
    }
  }
}
