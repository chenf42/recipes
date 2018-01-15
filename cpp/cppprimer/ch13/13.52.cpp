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

  HasPtr &operator=(HasPtr rhs) {
    std::cout << "Copy and swap\n";
    return *this;
  }
};

int main(int argc, char **argv) {
  HasPtr hp, hp2;

  // 输出：
  // Copy ctor
  // Copy and swap
  //
  // Copy ctor 将 hp2 拷贝到参数 rhs 中
  hp = hp2;

  std::cout << "--------\n";

  // 输出：
  // Move ctor
  // Copy and swap
  //
  // Move ctor 将 hp2 移动到参数 rhs 中
  hp = std::move(hp2);

  return 0;
}
