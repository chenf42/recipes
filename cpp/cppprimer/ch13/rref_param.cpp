#include <iostream>
#include <string>

void DoIt(const std::string &) {
  std::cout << "DoIt() lref\n";
}

void DoIt(std::string &&) {
  std::cout << "DoIt() rref\n";
}


void Do(const std::string &s) {
  std::cout << "Do() lref\n";
  DoIt(s);
}

void Do(std::string &&s) {
  std::cout << "Do() rref\n";
  // 虽然实参是右值，但到函数体内，已经发生过一次 move 动作，这里的 s 依然是左值！！
  // 因此下面的写法会调用 DoIt(const std::string &) 版本！！
  //DoIt(s);

  // 这才是正确写法
  DoIt(std::move(s));
}


int main(int argc, char **argv) {
  Do(std::string());

  return 0;
}

