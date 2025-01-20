

#include <functional>
#include <iostream>
#include <map>
#include <memory>


template <class Key, class Product> class Factory {
public:
  static Factory *getInstance() {
    std::cout << "Got Instance!\n";
    static Factory instance;
    return &instance;
  }

  std::unique_ptr<Product> createCommandByName(const Key &key) {
    auto command = commands_.find(key);
    if (command == commands_.end()) {
      return {};
      // throw std::runtime_error("Command not found");
    }
    return command->second(); // return creator for function
  }

  bool registerCreator(
      const Key &key,
      std::function<std::unique_ptr<Product>()> creator) {
    commands_[key] = creator;
    std::cout << "Registered!\n";
    return true;
  }

private:
  std::map<Key, std::function<std::unique_ptr<Product>()>>
      commands_;
};

template <class Key, class Product>
class Registrator {
 public:
  Registrator(){
        std::cout << "I'm here!";
    Factory<Key, Product>::getInstance()->registerCreator(
        Product::getFactoryName(),
        []() { return std::make_unique<Product>(); });
  }
  static bool registrate;
};

template <class Key, class Product>
bool Registrator<Key, Product>::registrate =
    Factory<Key, Product>::getInstance()->registerCreator(
        Product::getFactoryName(),
        []() { return std::make_unique<Product>(); });


class Test : public Registrator<std::string, Test>{
public:
  static std::string getFactoryName() { return "something"; }
private:
    static bool registrate;
};


int main(){
}
