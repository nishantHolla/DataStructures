
#ifndef TDS_LINKED_LIST_H_
#define TDS_LINKED_LIST_H_

#include <initializer_list>
#include <stddef.h>

namespace TDS {

template <typename T> class LinkedList {
public:
  struct Node {
    T data;
    Node *next;
  };

public:
  LinkedList();
  LinkedList(const std::initializer_list<T> &_init);

  size_t size() const;
  TDS::LinkedList<T>::Node *head() const;
  TDS::LinkedList<T>::Node *tail() const;

  void add(const T &_data);
  T &operator[](const size_t &_index);
  const T &operator[](const size_t &_index) const;
  T &at(const size_t &_index);
  const T &at(const size_t &_index) const;
  void insert(const T &_data, const size_t &_index);
  void insertAt(const T &_data, const size_t &_index);
  void remove(const size_t &_index);
  void removeAt(const size_t &_index);
  size_t removeAll(const T &_data);
  bool contains(const T &_data) const;
  size_t count(const T &_data) const;
  void map(void (*_mappingFunction)(T &_data));
  void filter(bool (*_filteringFunction)(T &_data));
  void reverse();
  bool empty() const;

  ~LinkedList();

private:
  void checkBound(const size_t &_index) const;
  size_t m_size;
  Node *m_head;
  Node *m_tail;
};

} // namespace TDS

#ifdef TDS_TEMPLATE
#include "linkedList.tpp"
#endif // TDS_TEMPLATE

#endif // !TDS_LINKED_LIST_H_
