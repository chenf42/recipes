#include <iostream>

class HasPtr {
public:
  HasPtr() {}

  HasPtr(HasPtr &&p) noexcept {
    std::cout << "Move ctor\n";
  }

  HasPtr(const HasPtr &p) {
    std::cout << "Copy ctor\n";
  }

  // 若不把此 copy and swap 版本去掉，下面的 copy/move assignment 在遇到适用的场景时，
  // 会报“不明确的重载”错误，无法编译。
  // HasPtr &operator=(HasPtr rhs) {
  //   std::cout << "Copy and swap\n";
  //   return *this;
  // }

  HasPtr &operator=(const HasPtr &rhs) {
    std::cout << "Copy assignment\n";
    return *this;
  }

  HasPtr &operator=(HasPtr &&rhs) noexcept {
    std::cout << "Move assignment\n";
    return *this;
  }
};

int main(int argc, char **argv) {
  HasPtr hp, hp2;

  // 只有一个 move assignment 操作，没有其他拷贝动作
  hp = std::move(hp2);
  return 0;
}
