#include <assert.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 需要前置声明，否则 Blob 中的
// friend class BlobPtr<T>
// 无法通过编译。
template <typename T> class BlobPtr;

template <typename T> class Blob;
// 友元函数需要前置声明
template <typename T> bool operator==(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator!=(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator<(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator>(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator<=(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator>=(const Blob<T> &, const Blob<T> &);

template <typename T>
class Blob {
public:
  // typedef T value_type;
  // typedef typename std::vector<T>::size_type size_type;
  // C++1x 中，建议用 using 替代 typedef
  using value_type = T;
  using size_type = typename std::vector<T>::size_type;  // 此处 typename 不可省略。否则编译报错。
  using iterator = BlobPtr<T>;
  //using const_iterator = const iterator;//const BlobPtr<T>;
  //typedef const iterator const_iterator;

  Blob() : data_(std::make_shared<std::vector<T>>()) {}
  Blob(std::initializer_list<T> il) : data_(std::make_shared<std::vector<T>>(il)) {}

  // 若使用此实现，则 Blob<T> 的拷贝构造是浅拷贝。
  // 根据书中描述，应该是需要这种实现方式。
  Blob(const Blob &other) : data_(other.data_) {}
  // 若使用此实现，则 Blob<T> 的拷贝构造是深拷贝
  //Blob(const Blob &other) : data_(std::make_shared<std::vector<T>>(*other.data_)) {}

  Blob(Blob &&other) : data_(std::move(other.data_)) {}

  Blob &operator=(const Blob &rhs) {
    data_ = rhs.data_;
    return *this;
  }

  Blob &operator=(Blob &&rhs) {
    if (this != &rhs) {
      data_ = std::move(rhs.data_);
      rhs.data_ = nullptr;
    }
    return *this;
  }

  iterator begin();
  iterator end();
  //const_iterator cbegin() const;
  //const_iterator cend() const;
  const iterator cbegin() const;
  const iterator cend() const;

  size_type size() const { return data_->size(); }
  bool empty() const { return data_->empty(); }

  void push_back(const T &val) { data_->push_back(val); }
  void push_back(T &&val) { data_->push_back(std::move(val)); }

  void pop_back() { data_->pop_back(); }

  const T &front() const { return data_->front(); }
  const T &back() const { return data_->back(); }
  const T &operator[](size_type index) const {
    check(index, "bad index");
    // TODO: 有别的写法吗？
    return (*data_)[index];
  }

  T &front() { return const_cast<T &>(static_cast<const Blob &>(*this).front()); }
  T &back() { return const_cast<T &>(static_cast<const Blob &>(*this).back()); }
  T &operator[](size_type index) {
    return const_cast<T &>(static_cast<const Blob &>(*this)[index]);
  }

  void DebugPrint() const {
    std::cout << "use_count: " << data_.use_count() << '\n';
  }

  friend class BlobPtr<T>;
  // 这里的 <T> 是必须要的
  // 在类代码内可以简化模板类名，不提供模板参数 T，但当前这个类是 Blob，
  // 只有 Blob 可以省略模板参数，其他友元类、函数都不能省去。
  friend bool operator==<T>(const Blob &, const Blob &);
  friend bool operator!=<T>(const Blob &, const Blob &);
  friend bool operator< <T>(const Blob &, const Blob &);  // 注意这里要空一格，要不两个<在一起编译器会报错
  friend bool operator><T>(const Blob &, const Blob &);
  friend bool operator<=<T>(const Blob &, const Blob &);
  friend bool operator>=<T>(const Blob &, const Blob &);
private:
  std::shared_ptr<std::vector<T>> data_;

  // 若 data_[i] 无效，则抛出 message
  void check(size_type i, const std::string &message) const {
    if (i >= size())
    //  throw message;
      throw std::out_of_range(message);
  }
};

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 运算符重载

template <typename T> bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) {
  // if (lhs.size() != rhs.size())
  //   return false;
  // // TODO: 此处用不用 typename 在 msvc1900 上都是可以编译的。进一步研究需要 typename 的时机。
  // for (/*typename*/ Blob<T>::size_type i = 0; i < lhs.size(); ++i) {
  //   if (lhs[i] != rhs[i])
  //     return false;
  // }
  // return true;

  // 213了，直接下面这样就可以了
  return *lhs.data_ == *rhs.data_;
}

template <typename T> bool operator!=(const Blob<T> &lhs, const Blob<T> &rhs) {
  return !(lhs == rhs);
}

template <typename T> bool operator<(const Blob<T> &lhs, const Blob<T> &rhs) {
  // for (Blob<T>::size_type i = 0; i < std::min(lhs.size(), rhs.size()); ++i) {
  //   if (lhs[i] < rhs[i])
  //     return true;
  //   if (lhs[i] > rhs[i])
  //     return false;
  // }
  // return lhs.size() < rhs.size();
  return std::lexicographical_compare(lhs.data_->begin(), lhs.data_->end(), rhs.data_->begin(), rhs.data_->end());
}

template <typename T> bool operator>(const Blob<T> &lhs, const Blob<T> &rhs) {
  // 这里太愚蠢了，显然无论怎样，颠倒一下操作数，就可以复用上面的实现。
  // for (Blob<T>::size_type i = 0; i < std::min(lhs.size(), rhs.size()); ++i) {
  //   if (lhs[i] < rhs[i])
  //     return false;
  //   if (lhs[i] > rhs[i])
  //     return true;
  // }
  // return lhs.size() > rhs.size();
  return rhs < lhs;
}

template <typename T> bool operator<=(const Blob<T> &lhs, const Blob<T> &rhs) {
  return !(lhs > rhs);
}

template <typename T> bool operator>=(const Blob<T> &lhs, const Blob<T> &rhs) {
  return !(lhs < rhs);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

template <typename T> bool operator==(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T> bool operator!=(const BlobPtr<T> &, const BlobPtr<T> &);

template <typename T>
class BlobPtr {
public:
  BlobPtr() : curr_(0) {}
  BlobPtr(Blob<T> &a, size_t sz = 0)
    : wptr_(a.data_),
      curr_(sz)
  {}

  T &operator*() {
    //auto p = check(curr_, "dereference past end");
    //return (*p)[curr_];
    return const_cast<T &>(*static_cast<const BlobPtr &>(*this));
  }

  const T &operator*() const {
    auto p = check(curr_, "dereference past end");
    return (*p)[curr_];
  }

  // 前置运算符
  BlobPtr &operator++() { curr_++; return *this; }
  BlobPtr &operator--() { curr_--; return *this; }

  // 后置运算符
  // 递增、递减对象但返回原值，故而这里返回 value 而非 reference
  BlobPtr operator++(int);
  BlobPtr operator--(int) {
    BlobPtr origin = *this;
    --*this;
    return origin;
  }

  friend bool operator==<T>(const BlobPtr &, const BlobPtr &);
  friend bool operator!=<T>(const BlobPtr &, const BlobPtr &);
private:
  std::shared_ptr<std::vector<T>> check(std::size_t index, const std::string &message) const {
    // if (!wptr_.expired()) {
    //   auto sp = wptr_.lock();
    //   if (index >= sp->size())
    //     throw message;
    //   return sp;
    // }
    // return std::shared_ptr<std::vector<T>>();
    auto sp = wptr_.lock();
    if (!sp) throw std::runtime_error("Unbound BlobPtr<T>");
    if (index > sp->size()) throw std::out_of_range(message);
    return sp;
  }

  std::weak_ptr<std::vector<T>> wptr_;
  std::size_t curr_;
};

// 注意：这里是类外部，因此 <T> 不能省略。
// 而一旦进入函数体内，又到了类内部，是可以省略的。
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
  BlobPtr origin = *this;
  // 调用前置运算符
  ++*this;
  return origin;
}

template <typename T> bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
  // TODO: 是否要确保两个 weak_ptr 指向同一个 Blob？
  return lhs.curr_ == rhs.curr_;
}

template <typename T> bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
  return !(lhs == rhs);
}

// 没法写这样的 using 语句。但也没有必要了，直接在 Blob<T> 里面定义 iterator / const_iterator 即可。
//template <typename T>
//using ConstBlobPtr<T> = const BlobPtr<T>;

template <typename T>
typename Blob<T>::iterator Blob<T>::begin() {
  return BlobPtr<T>(*this);
}

template <typename T>
typename Blob<T>::iterator Blob<T>::end() {
  return BlobPtr<T>(*this, size());
}

template <typename T>
const typename Blob<T>::iterator Blob<T>::cbegin() const {
  return BlobPtr<T>(*this);
}

template <typename T>
const typename Blob<T>::iterator Blob<T>::cend() const {
  return BlobPtr<T>(*this, size());
}

int main(int argc, char **argv) {
  /**
   * Blob<int> 基本测试
   */

  Blob<int> bi;
  Blob<int> bi0{{1,2}};  // 使用 initializer_list<int> 初始化
  assert(bi.empty());
  bi.push_back(1);
  bi.push_back(2);
  assert(bi.back() == 2);
  assert(bi.size() == 2);
  assert(bi == bi0);
  bi.pop_back();
  assert(bi.back() == 1);
  assert(bi.size() == 1);
  assert(bi != bi0);

  /**
   * Blob<std::string> 基本测试
   */

  Blob<std::string> bs({"hello", "world", "bye"});
  assert(bs.size() == 3);
  assert(bs.back() == "bye");
  assert(bs[1] == "world");
  bs[1] = "universe";
  bs.front() = "hi";
  assert(bs[0] == "hi");
  assert(bs[1] == "universe");
  assert(bs[2] == "bye");

  try {
    std::cout << bs[3];
    assert(0 && "should throw an exception");
  } catch (const std::out_of_range &) {
    // OK
  } catch (...) {
    assert(0 && "expected a std::out_of_range exception, but got exception with other type");
  }

  /**
   * 运算符重载测试
   */

  Blob<int> bi01 {{1,2,3}};
  Blob<int> bi02 {{2}};
  Blob<int> bi03 {{-1}};
  Blob<int> bi04 {{1,2,3}};
  assert(bi01 < bi02);
  assert(bi01 > bi03);
  assert(bi01 <= bi02);
  assert(bi01 <= bi04);
  assert(bi01 >= bi03);
  assert(bi01 >= bi04);
  assert(bi01 == bi04);
  assert(bi01 != bi03);

  /**
   * 拷贝/赋值
   */

  Blob<int> bi05 = bi01;  // Copy ctor
  bi01.DebugPrint();  // 2
  bi05.DebugPrint();  // 2

  Blob<int> bi06 = std::move(bi02);  // Move ctor
  bi06.DebugPrint();  // 1

  bi06 = bi03;  // Copy assignment
  bi06.DebugPrint();  // 2

  bi06 = std::move(bi03);  // Move assignment
  bi06.DebugPrint();  // 1

  /**
   * BlobPtr 测试
   */

  BlobPtr<int> unboundBpi;
  try {
    *unboundBpi;
    assert(0 && "should throw");
  } catch (const std::runtime_error &) {
    // OK
  } catch (...) {
    assert(0 && "unexpected exception type");
  }

  BlobPtr<int> bpi01 {bi01};
  assert(*bpi01 == 1);
  assert(*bpi01++ == 1);  // 后置++
  assert(*bpi01 == 2);
  assert(*++bpi01 == 3);  // 前置++
  assert(*bpi01-- == 3);  // 后置--
  assert(*bpi01 == 2);
  assert(*--bpi01 == 1);  // 前置--
  *bpi01 = 2;

  const BlobPtr<int> cbpi {bi01};
  assert(*cbpi == 2);
  // *cbpi = 3;   // 这里无法编译，因为不能修改常量，正是我们期望的结果

  /**
   * iterator / const_iterator 测试
   */
  Blob<int> bi000 {{1,2,3,4,5}};
  auto it = bi000.begin();
  assert(*it == 1);
  *it = 2;
  assert(*it == 2);

  for (auto i = bi000.begin(); i != bi000.end(); ++i) {
    (*i)++;
    std::cout << *i << ',';
  }
  std::cout << '\n';


  auto cit = bi000.cbegin();
  assert(*cit == 3);


  return 0;
}
