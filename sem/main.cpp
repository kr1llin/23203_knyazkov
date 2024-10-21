#include <iostream>
#include <stdexcept>

struct A {
  A() { std::cout << "ctor" << std::endl; }
  ~A() { std::cout << "dtor" << std::endl; }
};

// RAII: Resource Acquisition IS Initialization
// Ключевой способ управления ресурсами в Си++
class SmartPointerForA {
public:
  SmartPointerForA(A *a = nullptr) : a_(a) {}
  ~SmartPointerForA() { delete a_; }

  SmartPointerForA(SmartPointerForA&) = delete; // запретили копирование

private:
  A *a_ = nullptr;
};

void f() { throw std::runtime_error("error!!!"); }

void g() {
  SmartPointerForA smart(new A()); // Смартпоинтер теперь владеет ресурсом
  f();
}

int main() {
  try {
    g();
  } catch (...) {
    std::cerr << "Exception thrown!!" << std::endl;
  }
}
