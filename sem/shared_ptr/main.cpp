#include <iostream>

struct A {};

//Добавить наследование (добавляем ещё теймплейт)
//Метод удаление параметризованый (чтоб не вызывать делит)
template <class T> class SharedPtr {
public:
  SharedPtr(T *ptr = nullptr) : ptr_(ptr), counter_(new size_t(1)) {}
  SharedPtr(const SharedPtr<T> &other)
      : ptr_(other.ptr_), counter_(other.counter_) {
    (*other.counter_)++;
    counter_++;
  }

  SharedPtr(SharedPtr<T> &&other) : ptr_(other.ptr_), counter_(other.counter_) {
    (*counter_)--;
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  const SharedPtr<T> &operator=(const SharedPtr<T> &other) {
    if (this == &other)
      return *this;

    //if ptr_!=nullptr and counter >=1 --> reset

    delete ptr_;
    (*counter_)--;

    ptr_ = other.ptr_;
    counter_ = other.counter_;
    (*counter_) += 1;
//??????????????

    return *this;
  }

  const SharedPtr<T> &operator=(SharedPtr<T> &&other) {
    if (this == &other) {
      return *this;
    }

    delete ptr_;
    (*counter_)--;
    ptr_ = other.ptr_;
    counter_ = other.counter_;

    other.counter_ = nullptr;
    other.ptr_ = nullptr;

    return *this;
  }
  

  void reset(T *ptr) {
    if ((this->ptr_ != nullptr) && (*this->counter_ > 1)){
        delete ptr;
        counter_--;
    }
    if ((this->ptr_ != nullptr) && (*this->counter_ == 1)){
        delete ptr;
        delete counter_;
    }

    *this = SharedPtr(ptr);
  }

    //Отбросить прошлый поинтер и вернуть его
  T *release() {

  }

  ~SharedPtr() {
    if (counter_ && *counter_ > 0){
        (*counter_)--;
    }
    if (counter_ && *counter_ == 0){
        delete counter_;
        delete ptr_;
    }
  }

private:
  T *ptr_ = nullptr;
  size_t *counter_ = nullptr;
};

int main() {
  SharedPtr<A> p1(new A());
  SharedPtr<A> p2(new A());
  SharedPtr<A> p3 = p1;

  p1 = p2;

  p2.reset(new A());

  A *ppp = p3.release();
}
