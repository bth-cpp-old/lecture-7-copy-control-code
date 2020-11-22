#include <iostream>

class AClass {
  std::string s;

 public:
  AClass() { std::cout << "Entering default constructor" << std::endl; }

  AClass(std::string s) : s(s) {
    std::cout << "Entering constructor for: " << s << std::endl;
  }

  AClass(AClass& other) : s("Copy of " + other.s) {
    std::cout << "Entering copy-constructor for: " << s << std::endl;
  }

  ~AClass() { std::cout << "Entering destructor for: " << s << std::endl; }

  AClass& operator=(const AClass& rhs) {
    s = rhs.s;
    std::cout << "Entering assignment-operator for: " << s << std::endl;
    return *this;
  }

  void memberFunction() {
    std::cout << "Entering memberFunction for: " << s << std::endl;
  }
};

void ctorDtor() {
  std::cout << "\nhello\n";

  std::cout << "\non stack\n";
  {
    AClass aclass("stack");
    aclass.memberFunction();
  }

  std::cout << "\nonHeap\n";
  {
    AClass* aclass = nullptr;
    aclass = new AClass("heap");
    aclass->memberFunction();
  }

  std::cout << "\nDefault\n";
  {
    AClass aclass;
    aclass.memberFunction();
  }

  std::cout << "\ncopy\n";
  {
    AClass toCopy("original");
    AClass aclass = toCopy;
    aclass.memberFunction();
  }

  std::cout << "\nassignment\n";
  {
    AClass first("first");
    AClass second("second");
    first = second;
    first.memberFunction();
    second.memberFunction();
  }

  std::cout << "\ngoodbye\n";
}