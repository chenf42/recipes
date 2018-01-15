#include <iostream>
#include <string>

class Foo {
public:
  // 后面加 & （引用限定符）之后，下面的 f1 + f2 = f3; 就会编译报错了。
  // 该语法限定的赋值操作的左操作数必须是个可修改的左值
  Foo &operator=(const Foo &) & {
    return *this;
  }

  Foo operator+(const Foo &) {
    return Foo();
  }

  // && 表示只能用于右值对象
  Foo sorted() && {
    std::cout << "&&\n";
    return Foo();
  }

  // 这个版本有问题， ret 也是左值，因此会不定调用自身，导致爆栈
  // Foo sorted() const & {
  //   std::cout << "&\n";
  //   Foo ret(*this);
  //   return ret.sorted();
  // }

  // 这个版本 OK，因为 Foo(*this) 产生了一个右值，会调用上面的对应版本
  Foo sorted() const & {
    std::cout << "&\n";
    return Foo(*this).sorted();
  }
};

int main(int argc, char **argv) {
  std::string s1("hello"), s2("world");
  // 产生的一个临时 string 对象来保存 s1 + s2 的结果，该对象是个右值，但我们仍然可以
  // 对其赋值，虽然没有任何意义。
  s1 + s2 = "bye";

  Foo f1, f2, f3;
  //f1 + f2 = f3;
  //(f1 + f2).sorted();

  f2.sorted();

  return 0;
}
