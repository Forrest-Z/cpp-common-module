
#include <gtest/gtest.h>

#include <condition_variable>
#include <mutex>
#include <thread>

class Base {
 public:
  virtual int a() = 0;
};

#include <iostream>
class B;

template <class MSG, class T>
class A : public Base {
 protected:
  int e = 1, f = 2, g = 4;
  MSG msg;

 public:
  virtual int a() { 
    ((B *)this)->c();
    
    return ((T *)this)->c(); }
};

class A_INTERFACE : public A<int, A_INTERFACE> {
 public:
  int c() {
    msg = e + f + g;
    return e + f + g;
  }
};

class B : public A<int, A_INTERFACE> {
    public:
  int h = 2134;
  int c() { return 123456; }
};

TEST(std, crtp) {
  B b;
  std::cout << "Hello World " << b.a();
}