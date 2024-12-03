#include "forth.hpp"

#include <string>

class UserInterface {
public:
    void printStack() const;

    static UserInterface& getInstance() {
        static UserInterface instance; 
        return instance;               
    }

     void printStack(const Forth& forth) const;

    UserInterface(const UserInterface&) = delete;
    UserInterface& operator=(const UserInterface&) = delete;

    void displayMessage(const std::string& message) {
        putL();
        std::cout << message << std::endl;
    }

    // void displayOutput(const std::string& message) {
    //     putL();
    //     std::cout << message << std::endl;
    // }

    inline void putG() { std::cout << "> "; }
    inline void putL() { std::cout << "< "; }


    std::string getUserInput() {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

private:
    UserInterface() {}
};
