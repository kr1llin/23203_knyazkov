#include <iostream>

class Vector {
public:
  Vector() {
    Reallocate(2);
    currentSize = 0;
  }

  Vector(size_t size) {
    capacity = size;
    currentSize = 0;
    Reallocate(size);
  }

  ~Vector() { delete[] data; };

  // copy constructor
  Vector(const Vector &v)
      : currentSize(v.currentSize), data(new int[v.currentSize]) {
    std::copy(v.data, v.data + v.currentSize, data);
  }

  // assignment operation for copy
  Vector &operator=(const Vector &v) {
    if (this != &v) {
      delete[] data;
      currentSize = v.currentSize;
      data = new int[currentSize];
      std::copy(v.data, v.data + currentSize, data);
    }
    return *this;
  }

  // move constructor
  Vector(Vector &&v) noexcept : currentSize(v.currentSize), data(v.data) {
    v.currentSize = 0;
    v.data = nullptr;
  }

  // move operation
  Vector &operator=(Vector &&v) noexcept {
    if (this != &v) {
      delete[] data;
      currentSize = v.currentSize;
      data = v.data;
      v.currentSize = 0;
      v.data = nullptr;
    }
    return *this;
  }

  //pushback with copies
  void PushBack(const int &item) {
    if (currentSize >= capacity)
      Reallocate(capacity + capacity / 2); // will grow by 50%

    data[currentSize] = item;
    currentSize++;
  }

  // pushback without copies
  void PushBack(int &&item) {
    if (currentSize >= capacity)
      Reallocate(capacity + capacity / 2); // will grow by 50%

    data[currentSize] = std::move(item);
    currentSize++;
  }

  size_t getSize() const { return currentSize; }

  size_t getCapacity() const { return capacity; }

  void Print() {
    for (size_t i = 0; i < currentSize; i++) {
      std::cout << data[i] << " ";
    }
    std::cout << '\n';
  }
//square pearentheses operator
  int &operator[](size_t id) { return data[id]; }

private:
  int *data = nullptr;
  size_t currentSize = 0; // Number of elements inside Vector
  size_t capacity = 0;

private:
  // Allocates block of memory and copies/moves old elements to new block
  void Reallocate(size_t newCapacity) {
    int *newChunk = new int[newCapacity];

    if (newCapacity < currentSize)
      currentSize = newCapacity;

    for (size_t i = 0; i < currentSize; i++)
      newChunk[i] = data[i];

    delete[] data;
    data = newChunk;
    capacity = newCapacity;
  }
};

int main() {

  Vector a, b;

  std::cout << "Push element to a: ";
  int item;
  std::cin >> item;
  a.PushBack(item);
  std::cout << "First element of a: " << a[0] << '\n';
  std::cout << "Push element to b: ";
  std::cin >> item;
  b.PushBack(item);
  a = b;
  std::cout << "a after \"a=b\": ";
  a.Print();
}
