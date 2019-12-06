#ifndef STACK_H
#define STACK_H
#include <cstdlib> //allows us to use size_t
#include <cassert> //allows us to use assert
//implementation as an array
using namespace std;

template <typename T>
class Stack{
public:
  static const size_t CAPACITY = 50; //max size of array of implementation
  Stack(){ used = 0;} //initializes the stack as empty
  void pop();
  void push(const T& entry);
  T top() const;
  bool empty() const {
    return used==0;
  }
  size_t size() const {
    return used;
  }
private:
  T data[CAPACITY];
  size_t used;
};

//precondition: size() > 0
//postcondition: the top item of the stack is removed
template <typename T>
void Stack<T>:: pop(){
  assert(!empty());
  used--;
}

//precondition: size() < CAPACITY
//postcondition: a new copy of the entry has been pushed into the stack
template <typename T>
void Stack<T>:: push(const T& entry){
  assert(size() < CAPACITY);
  data[used] = entry;
  used++;
}

//precondition: size() > 0
//postcondition: return value is the top item of stack but stack isn't affected
template <typename T>
T Stack<T>:: top() const{
  assert(!empty());
  return data[used-1];
}

#endif
