#include <iostream>

struct MyStruct {
  MyStruct() { std::cout << "MyStruct ctor\n"; }

  MyStruct(const MyStruct &other) {
    std::cout << "MyStruct copy ctor\n";
  }

  MyStruct &operator=(const MyStruct &other) {
    std::cout << "MyStruct copy assignment\n";
    return *this;
  }
};

MyStruct Ret1() {
  MyStruct ret;
  return ret;
}

struct MyStruct2 {
  int i;

  MyStruct2(int ii) : i(ii) { std::cout << "MyStruct2 ctor\n"; }

  MyStruct2(const MyStruct2 &other) {
    std::cout << "MyStruct2 copy ctor\n";
  }

  MyStruct2(MyStruct2 &&other) {
    std::cout << "MyStruct2 move ctor\n";
  }

  MyStruct2 &operator=(const MyStruct2 &other) {
    std::cout << "MyStruct2 copy assignment\n";
    return *this;
  }

  MyStruct2 &operator=(MyStruct2 &&other) {
    std::cout << "MyStruct2 move assignment\n";
    return *this;
  }
};

MyStruct2 Ret2() {
  // 编译器知道 ret 在函数返回时会被销毁，因此这里会使用 move ctor 来将其返回
  // MyStruct2 ret(100);
  // return ret;

  // 这种写法貌似会只调用一次 ctor，连 move 都不需要了
  // 经试验，即使在 C++98 编译器（Borland C++ 5）上，也是只调用一次 ctor，不需要 copy
  // 这里是编译器施加了 return value optimization，参考 https://stackoverflow.com/questions/12953127/what-are-copy-elision-and-return-value-optimization
  return MyStruct2(100);
}


int main(int argc, char **argv) {
  auto r1 = Ret1();

  auto r2 = Ret2();
  std::cout << r2.i << '\n';

  return 0;
}
