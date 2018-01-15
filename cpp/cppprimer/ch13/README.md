

## 13.45：解释右值引用和左值引用的区别。

左值引用：可以绑定到左值的引用。持久。
右值引用：绑定到即将被销毁的右值的引用。短暂。

## 13.46：什么类型的引用可以绑定到下面的初始化器上？

```c++
int f();
vector<int> vi(100);
int&& r1 = f1();
int& r2 = vi[0];
int& r3 = r1;
int&& r3 = vi[0] * f();
```

## 13.47：对你在练习 13.44 中定义的 String 类，为它的拷贝构造函数和拷贝赋值运算添加一条语句，在每次函数执行时打印一条信息。

见 13.48 代码。

## 13.48：定义一个 vector<String> 并在其上多次调用 push_back。运行你的程序，并观察 String 被拷贝了多少次。

[代码](/cpp/cppprimer/ch13/13.48.cpp)

std::vector 的 capacity 增长策略是 capacity *= 1.5。当 vector<String> 的 capacity 为默认的 0 时，5 次 push_back 都会发生存储空间的重新分配。以第 5 次为例， push_back 操作调用了一次拷贝构造，之前的 4 个元素的移动也各调用了一次拷贝构造。若 capacity 大于等于 5，即没有存储空间的重新分配，那么每次 push_back 只导致一次拷贝构造动作。

## 13.49：为你的 StrVec、String 和 Message 类添加一个移动构造函数和一个移动赋值运算符。

```C++
class String {
  char *data_;
  size_t len_;

public:
  // ...

  String(String &&other) noexcept
    : data_(other.data_),
      len_(other.len_) {
    other.data_ = nullptr;
    other.len_ = 0;
  }

  String &operator=(String &&other) noexcept {
    if (this != &other) {
      ::operator delete(data_);

      data_ = other.data_;
      len_ = other.len_;

      other.data_ = nullptr;
      other.len_ = 0;
    }
    return *this;
  }
};
```

## 13.50：在你的 String 类的移动操作中添加打印语句，并重新运行 13.48 中的程序，观察什么时候回避免拷贝。

见 13.48 代码。

## 13.51：虽然 unique_ptr 不能拷贝，但我们在 12.1.5 节（第 418 页）中编写了一个 clone 函数，它以值方式返回了一个 unique_ptr。解释为什么函数是合法的。以及为什么它能正确工作。

编译器知道要返回的对象即将被销毁，因此会执行 move assignment 而非 copy assignment。[额外实验代码](/cpp/cppprimer/ch13/return_local_variable.cpp)

## 13.52：详细解释第 478 页中的 HasPtr 对象的赋值发生了什么？特别是，一步步描述 hp、hp2 以及 HasPtr 的赋值运算符中的参数 rhs 的值发生了什么变化。

[代码](/cpp/cppprimer/ch13/13.52.cpp)

## 13.53：从底层效率的角度看，HasPtr 的赋值运算符并不理想，解释为什么。为 HasPtr 实现一个拷贝赋值运算符和一个移动赋值运算符，并比较你的新的移动赋值运算符中执行的操作和拷贝并交换版本中执行的操作。

在执行`hp = hp2;`时，拷贝并交换（Copy and Swap）版本需要执行一次 Copy ctor 将 hp2 拷贝到 rhs 中，然后执行 Copy and Swap 动作；而移动赋值运算符版本不需要参数拷贝动作，直接执行 Move assignment 动作。应该是比前者高效的。

## 13.54：如果我们为 HasPtr 定义了移动赋值运算符，但未改变拷贝并交换运算符，会发生什么？编写代码验证你的答案。

会报“重载不明确”的编译错误。

## 13.55：为你的 StrBlob 添加一个右值引用版本的 push_back。

```C++
void push_back(string &&s) { data_->push_back(std::move(s)); }
```
[额外实验代码](/cpp/cppprimer/ch13/rref_param.cpp)

## 13.56：如果 sorted 定义如下，会发生什么:
```c++
Foo Foo::sorted() const & {
  Foo ret(*this);
  return ret.sorted();
}
```

`ret` 是个左值，因此上面函数会不断调用自身，导致爆栈。

## 13.57：如果 sorted 定义如下，会发生什么:
```c++
Foo Foo::sorted() const & { return Foo(*this).sorted(); }
```

`Foo(*this)` 产生了一个右值对象，这种写法没问题。

## 13.58：编写新版本的 Foo 类，其中 sorted 函数中有打印语句，测试这个类，来验证你前两题的答案是否正确。

[代码](/cpp/cppprimer/ch13/13.58.cpp)
