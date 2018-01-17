#include <iostream>

class Foo {
public:
  Foo() {}

  // 如果定义了 move ctor，那么编译器就会删除 copy ctor / copy assignment。
  // 就是说，不需要再去继承 boost::noncopyable 来定义为不可拷贝了。
  Foo(Foo &&) {}
};

int main(int argc, char **argv) {
  Foo f1, f2;
  //f1 = f2;
  //Foo f3(f2);
  return 0;
}
