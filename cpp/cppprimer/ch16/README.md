# 读书笔记

p.582 编译器对模板处理的三个阶段：

1. 编译模板本身：检查基本语法是否正确等。
2. 编译器遇到模板使用时的处理：检查模板实参数目是否正确等等。
3. 实例化：这个阶段才能发现类型相关的错误。发现的错误可能在链接器才会报。

# 习题解答

## 16.1：给出实例化的定义。

编译器用实参来推导出模板参数的类型，并生成对应此类型的的类或函数代码。

## 16.2：编写并测试你自己的 compare 函数。

[compare 实现](/cpp/cppprimer/ch16/compare.h)

[测试](/cpp/cppprimer/ch16/16.2.cpp)

## 16.3：对两个 Sales_data 对象调用你的 compare 函数，观察编译器在实例化过程中如何处理错误。

“未定义运算符或到预定义运算符可接受的类型的转换”。

[代码](/cpp/cppprimer/ch16/16.3.cpp)

## 16.4：编写行为类似标准库 find 算法的模板。函数需要两个模板类型参数，一个表示函数的迭代器类型，另一个表示值的类型。使用你的函数在一个 vector<int> 和一个 list<string> 中查找给定值。

[代码](/cpp/cppprimer/ch16/16.4.cpp)

## 16.5：为 6.2.4 节（第 195 页）中的 print 函数编写模板版本。它能接受一个数组的引用，能处理任意大小、任意元素类型的数组。

```C++
template <typename T, size_t N>
void Print(T (&a)[N]) {
  //for (auto elem : a)  // TODO: 阅读 Effective Modern C++ 前两章
  for (const auto &elem : a)
    std::cout << elem << '\n';
}
```

## 16.6：你认为接受一个数组实参的标准库函数 begin 和 end 是如何工作的？

```C++
template <typename T, size_t N> T *begin(T (&a)[N]) { return a; }

template <typename T, size_t N> T *end(T (&a)[N]) { return a + N; }
```

## 16.7：编写一个 constexpr 模板，返回给定数组的大小。

```C++
template <typename T, size_t N> constexpr size_t ArraySize(T (&a)[N]) { return N; }
```

## 16.8：我们注意到，C++程序员喜欢使用!=而不喜欢<。解释这个习惯的原因。

标准库容器的迭代器都定义了==和!=，但大多数没有定义<运算符。

## 16.9：什么是函数模板？什么是类模板？

一个可以实例化出函数，一个可以实例化出类。区别在于：函数模板的参数类型可以根据实参类型推导出来；而类模板的参数无法推导，所以我们要在尖括号中给出参数列表。

## 16.10：当一个类模板被实例化，会发生干什么？

对每个被使用的实例，编译器使用该实例的模板参数替代 T，生成对应的类代码。

## 16.11：下面 List 的定义是错误的。应该如何修正？

```C++
template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
  List<elemType>();
  List<elemType>(const List<elemType> &);
  List<elemType> &operator=(const List<elemType> &);
  ~List();

  void insert(ListItem *ptr, elemType value);
private:
  ListItem *front, *end;
};
```

修正版本：
```C++
template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
  List();
  List(const List &);
  List &operator=(const List &);
  ~List();

  void insert(ListItem<elemType> *ptr, elemType value);
private:
  ListItem<elemType> *front, *end;
};
```

## 16.12：编写你自己版本的 Blob 和 BlobPtr 模板，包含书中未定义的多个 const 成员。


