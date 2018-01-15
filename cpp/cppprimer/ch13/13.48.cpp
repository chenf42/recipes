#include <iostream>
#include <vector>

class String {
public:
  String() {
    std::cout << "Ctor\n";
  }

  String(const String &other) {
    std::cout << "Copy ctor\n";
  }

  String &operator=(const String &other) {
    std::cout << "Copy assignment\n";
  }

  String(String &&other) {
    std::cout << "Move\n";
  }
};

int main(int argc, char **argv) {
  std::vector<String> v;

  for (auto i = 0; i < 5; ++i) {
    std::cout << "-----------\n";
    std::cout << "capacity: " << v.capacity() << '\n';
    v.push_back(String());
  }

  std::cout << "========\n";
  v.clear();
  std::cout << "capacity: " << v.capacity() << '\n';
  for (auto i = 0; i < 5; ++i) {
    std::cout << "-----------\n";

    // 若使用下面这条语句，会调用 push_back(Type &&_Val) 版本，Move copy ctor 会被调用
    //v.push_back(String());

    // 此处 tmp 是个左值，会调用 push_back(const Type &_Val)版本，Copy ctor 会被调用
    String tmp;
    v.push_back(tmp);
  }

  std::cout << "=======\n";
  //std::vector<String> v2;
  v.clear();
  for (auto i = 0; i < 5; ++i) {
    std::cout << "-----------\n";

    // 同上 push_back(Type &&_Val) 版本
    //v.emplace_back(String());

    // 同上 push_back(const Type &_Val) 版本
    //String tmp;
    //v.emplace_back(tmp);

    // NOTE:! emplace_back(Args&& ...) 的牛逼之处在于，它可以接受元素类型的构造函数所需的参数，
    // 并将它们转发给构造函数，因此，插入操作只需要一次 ctor 调用。而非 ctor + copy 或者 ctor + move。
    // 因此它很高效。
    v.emplace_back();

  }

  return 0;
}
