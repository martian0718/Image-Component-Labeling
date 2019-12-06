#ifndef AQUEUE_H
#define AQUEUE_H

#include <cstdlib>
#include <cassert>

using namespace std;

template <typename T>
class AQueue {
public:
  static const size_t CAPACITY = 30;
  AQueue();
  void pop();
  void push(const T& entry);
  bool empty() const { return count==0;}
  T front() const;
  size_t size() const {return count;}
private:
  T data[CAPACITY];
  size_t first;
  size_t last;
  size_t count;
  //helper member functions
  size_t next_index(size_t i) const { return (i+1) % CAPACITY;}
};

template <typename T>
AQueue<T>:: AQueue() {
  count = 0;
  first = 0;
  last = CAPACITY - 1;
}

template <typename T>
T AQueue<T>:: front() const {
  assert(!empty());
  return data[first];
}

template <typename T>
void AQueue<T>:: pop() {
  assert(!empty());
  first = next_index(first);
  --count;
}

template <typename T>
void AQueue<T>:: push(const T& entry){
  assert(size() < CAPACITY);
  last = next_index(last);
  data[last] = entry;
  ++count;
}

#endif
