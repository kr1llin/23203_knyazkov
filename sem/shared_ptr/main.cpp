#include <cstddef>
#include <iostream>

struct A {};

class B {
public:
    virtual ~B() {}
    virtual void show() const = 0;
};

class C : public B {
public:
    void show() const override {
        std::cout << "Derived" << std::endl;
    }
};


// Добавить наследование (добавляем ещё теймплейт)
// Метод удаление параметризованый (чтоб не вызывать делит)
template <class T> class SharedPtr {
public:
  SharedPtr() : ptr_(nullptr), counter_(new size_t(0)){}; //default constructor
  SharedPtr(T *ptr = nullptr) : ptr_(ptr), counter_(new size_t(1)) {}
  SharedPtr(const SharedPtr<T> &other) // copy constructor
      : ptr_(other.ptr_), counter_(other.counter_) {
    if (nullptr != other.ptr_) {
      (*counter_)++;
    }
  }

  //move constructor
  SharedPtr(SharedPtr<T> &&other) : ptr_(other.ptr_), counter_(other.counter_) {
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  //copy assignment
  const SharedPtr<T> &operator=(const SharedPtr<T> &other) {
    if (this == &other)
      return *this;

    if (ptr_ != nullptr && (*counter_ ) >= 1){
      release();
    }

    ptr_ = other.ptr_;
    counter_ = other.counter_;
    if (nullptr != other.ptr_){
      (*counter_)++;
    }

    return *this;
  }

  //move assignment
  const SharedPtr<T> &operator=(SharedPtr<T> &&other) {
    if (this == &other) {
      return *this;
    }

    release();

    ptr_ = other.ptr_;
    counter_ = other.counter_;

    other.counter_ = nullptr;
    other.ptr_ = nullptr;

    return *this;
  }

  //clean up
  void reset(T *ptr) {
    release();
    *this = SharedPtr(ptr);
  }

  // Отбросить прошлый поинтер и вернуть его
  T *release() {
    T* saved_p = ptr_;

   if (counter_ && *counter_ > 0) {
      (*counter_)--;
    }
    if (counter_ && *counter_ == 0) {
      delete counter_;
      counter_ = nullptr;
      delete ptr_;
      ptr_ = nullptr;
    }

    ptr_ = nullptr;

    return saved_p;
  }

   T* operator->() const {
        return ptr_;
    }

  ~SharedPtr() {
   release();
  }

private:
  T *ptr_ = nullptr;
  size_t *counter_ = nullptr;
};

int main() {
  SharedPtr<B> ptr1(new C());
  ptr1->show(); 

  SharedPtr<A> p1(new A());
  SharedPtr<A> p2(new A());
  SharedPtr<A> p3 = p1;

  p1 = p2;
  p2.reset(new A());
  A *ppp = p3.release();
}
