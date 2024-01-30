
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#ifndef TDS_TEMPLATE
#include "linkedList.hpp"
#endif // !TDS_TEMPLATE

#define templated template <typename T>
#define LinedkListNode typename TDS::LinkedList<T>::Node

templated TDS::LinkedList<T>::LinkedList()
    : m_size(0), m_head(nullptr), m_tail(nullptr) {}

templated TDS::LinkedList<T>::LinkedList(const std::initializer_list<T> &_init)
    : m_size(0), m_head(nullptr), m_tail(nullptr) {
  for (const T &element : _init) {
    add(element);
  }
}

templated size_t TDS::LinkedList<T>::size() const { return m_size; }
templated LinedkListNode *TDS::LinkedList<T>::head() const { return m_head; }
templated LinedkListNode *TDS::LinkedList<T>::tail() const { return m_tail; }

templated void TDS::LinkedList<T>::add(const T &_data) {
  Node *newNode = new Node{_data, nullptr};

  if (!m_head) {
    m_head = newNode;
  } else {
    m_tail->next = newNode;
  }

  m_tail = newNode;
  m_size++;
}

templated T &TDS::LinkedList<T>::operator[](const size_t &_index) {
  Node *current = m_head;
  for (size_t i = 0; i < _index; i++)
    current = current->next;

  return current->data;
}

templated const T &TDS::LinkedList<T>::operator[](const size_t &_index) const {
  Node *current = m_head;
  for (size_t i = 0; i < _index; i++)
    current = current->next;

  return current->data;
}

templated T &TDS::LinkedList<T>::at(const size_t &_index) {
  checkBound(_index);
  return (*this)[_index];
}

templated const T &TDS::LinkedList<T>::at(const size_t &_index) const {
  checkBound(_index);
  return (*this)[_index];
}

templated void TDS::LinkedList<T>::insert(const T &_data,
                                          const size_t &_index) {
  if (_index == m_size) {
    add(_data);
    return;
  }

  m_size++;
  Node *newNode = new Node{_data, nullptr};
  if (_index == 0) {
    newNode->next = m_head;
    m_head = newNode;
    return;
  }

  Node *prev = m_head;
  for (int i = 1; i < _index; i++)
    prev = prev->next;

  newNode->next = prev->next;
  prev->next = newNode;
}

templated void TDS::LinkedList<T>::insertAt(const T &_data,
                                            const size_t &_index) {
  checkBound(_index);
  insert(_data, _index);
}

templated void TDS::LinkedList<T>::remove(const size_t &_index) {
  m_size--;

  if (_index == 0) {
    Node *temp = m_head;
    m_head = m_head->next;
    delete temp;
    return;
  }

  Node *current = m_head;
  for (int i = 1; i < _index; i++)
    current = current->next;

  Node *temp = current->next;

  if (temp == m_tail)
    m_tail = current;

  current->next = temp->next;
  delete temp;
}

templated void TDS::LinkedList<T>::removeAt(const size_t &_index) {
  checkBound(_index);
  remove(_index);
}

templated size_t TDS::LinkedList<T>::removeAll(const T &_data) {
  size_t initSize = m_size;
  Node *current = m_head;
  size_t i = 0;

  while (current) {
    if (current->data == _data) {
      current = current->next;
      remove(i);
      continue;
    }
    i++;
    current = current->next;
  }
  return initSize - m_size;
}

templated bool TDS::LinkedList<T>::contains(const T &_data) const {
  Node *current = m_head;

  while (current) {
    if (current->data == _data)
      return true;

    current = current->next;
  }

  return false;
}

templated size_t TDS::LinkedList<T>::count(const T &_data) const {
  size_t count = 0;
  Node *current = m_head;

  while (current) {
    if (current->data == _data)
      count++;
    current = current->next;
  }

  return count;
}

templated void TDS::LinkedList<T>::map(void (*_mappingFunction)(T &_data)) {
  Node *current = m_head;

  while (current) {
    _mappingFunction(current->data);
    current = current->next;
  }
}

templated void
TDS::LinkedList<T>::filter(bool (*_filteringFunction)(T &_data)) {
  Node *current = m_head;

  size_t index = 0;
  while (current) {
    if (_filteringFunction(current->data)) {
      current = current->next;
      remove(index);
      continue;
    }
    index++;
    current = current->next;
  }
}

templated void TDS::LinkedList<T>::reverse() {
  if (m_size < 2)
    return;

  if (m_size == 2) {
    m_head->next = nullptr;
    m_tail->next = m_head;
    std::swap(m_head, m_tail);
    return;
  }

  Node *left = m_head;
  Node *middle = m_head->next;
  Node *right = m_head->next->next;
  m_tail = m_head;
  m_head->next = nullptr;

  while (right) {
    middle->next = left;
    left = middle;
    middle = right;
    right = right->next;
  }
  middle->next = left;

  m_head = middle;
}

templated bool TDS::LinkedList<T>::empty() const { return m_size == 0; }

templated void TDS::LinkedList<T>::checkBound(const size_t &_index) const {
  if (_index < 0 || _index > m_size - 1)
    throw std::out_of_range("Accessing " + std::to_string(_index) + " of " +
                            std::to_string(m_size));
}

templated TDS::LinkedList<T>::~LinkedList() {
  Node *current = m_head;
  size_t c = 0;

  while (current) {
    Node *temp = current;
    current = current->next;
    c++;
    delete temp;
  }

  std::cout << "Free: " << c << "\n";
}
