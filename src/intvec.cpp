#include <iostream>

class Intvec {
 private:
  void log(const char* msg) { std::cout << "[" << this << "] " << msg << "\n"; }

  size_t m_size;
  int* m_data;

 public:
  explicit Intvec(size_t num = 0) : m_size(num), m_data(new int[m_size]) {
    log("constructor");
  }

  ~Intvec() {
    log("destructor");
    if (m_data != nullptr) {
      delete[] m_data;
      m_data = nullptr;
    }
  }

  Intvec(const Intvec& other) : m_size(other.m_size), m_data(new int[m_size]) {
    log("copy constructor");
    for (size_t i = 0; i < m_size; ++i) {
      m_data[i] = other.m_data[i];
    }
  }

  // Intvec& operator=(const Intvec& other) {
  //   log("copy assignment operator");
  //   if (m_data != nullptr) {
  //     delete[] m_data;
  //   }

  //   m_size = other.m_size;
  //   m_data = new int[m_size];
  //   for (size_t i = 0; i < m_size; ++i) {
  //     m_data[i] = other.m_data[i];
  //   }

  //   return *this;
  // }

  Intvec& operator=(const Intvec& other) {
    log("copy assignment operator");
    Intvec tmp(other);
    std::swap(m_size, tmp.m_size);
    std::swap(m_data, tmp.m_data);
    return *this;
  }

  Intvec(Intvec&& other) noexcept : m_size(other.m_size), m_data(other.m_data) {
    log("move constructor");
    other.m_data = nullptr;
    other.m_size = 0;
  }

  Intvec& operator=(Intvec&& other) {
    log("move assignment operator");
    std::swap(m_size, other.m_size);
    std::swap(m_data, other.m_data);
    return *this;
  }
};

void intvec() {
  Intvec v1(10);
  Intvec v2(20);

  std::cout << "\ncopy constructor with lvalue...\n";
  Intvec v3 = v1;
  std::cout << "ended copy constructor with lvalue...\n";

  std::cout << "\nassigning lvalue...\n";
  v2 = v1;
  std::cout << "ended assigning lvalue...\n";

  std::cout << "\nmove constructor with rvalue...\n";
  Intvec v4 = Intvec(42);
  std::cout << "ended move constructor with rvalue...\n";

  std::cout << "\nassigning rvalue...\n";
  v2 = Intvec(33);
  std::cout << "ended assigning rvalue...\n";

  std::cout << std::endl;
}
