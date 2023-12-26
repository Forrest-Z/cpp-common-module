
#include <gtest/gtest.h>

#include <functional>
#include <string>
#include <thread>

typedef std::function<bool(int data, std::string name)> FuncType;

class FunctionDemo {
 public:
  FunctionDemo(FuncType func) : func(func) {
    thr = std::thread(std::bind(&FunctionDemo::Run, this));
  }
  ~FunctionDemo() {
    thr.join();
    std::cout << "~FunctionDemo " << std::endl;
  }

  FuncType Get() {
    return std::bind(&FunctionDemo::FuncPrivate, this, std::placeholders::_1,
                     std::placeholders::_2);
  }

 private:
  void Run() {
    int cnt = 10;
    while (cnt--) {
      sleep(1);
      auto ret = this->func(cnt, name);
      std::cout << "ret: " << ret << std::endl;
    }
  }

  bool FuncPrivate(int cnt, std::string name) {
    std::cout << "run Demo " << this->name << " Private func " << cnt << " "
              << name << std::endl;
  }

  std::string name = "FunctionDemo";

  FuncType func;
  std::thread thr;
};

TEST(boost, functional) {
  FuncType f = [](int data, std::string name) -> bool {
    std::cout << "f " << name << " " << data << std::endl;
  };

  FunctionDemo demo(f);
  auto f2 = demo.Get();

  f2(10000000, "f2");

  std::cout << "------end --------" << std::endl;
}