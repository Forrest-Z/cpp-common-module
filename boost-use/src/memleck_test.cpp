// Online C++ compiler to run C++ program online
#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <thread>


class DataManager {
 public:

 protected:
  DataManager() {}

 public:
  DataManager(DataManager &other) = delete;
  void operator=(const DataManager &) = delete;

  static DataManager &GetInstance( ) {
    static DataManager instance; 
    return instance;
  }
};

class Derived : public DataManager {
public:
  Derived(Derived &other) = delete;
  void operator=(const Derived &) = delete;

  static Derived *GetInstance() {
    return (Derived *) &DataManager::GetInstance();
  }
  
  void print(){
      std::cout << "derived print";

  }
public:
    int a[10000000000000];
};

TEST(memleck, a) {
    Derived::GetInstance()->print();
    for (size_t i = 0; i < sizeof(Derived::GetInstance()->a)/sizeof(int); i++)
    {
       std::cout << "Try programiz.pro : " <<     Derived::GetInstance()->a[i];
       Derived::GetInstance()->a[i] = i;
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    

    // Write C++ code here
    

}