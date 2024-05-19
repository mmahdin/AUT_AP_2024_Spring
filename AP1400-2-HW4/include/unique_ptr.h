#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <iostream>
template <typename T>
class UniquePtr {
 public:
  UniquePtr(T* p);
  UniquePtr() : _p{nullptr} {};
  ~UniquePtr();
  UniquePtr(const UniquePtr<T>& other) = delete;
  UniquePtr<T>& operator=(const UniquePtr<T>& other) = delete;
  T& operator*();
  T* operator->();
  operator bool() {
    if (_p == nullptr)
      return false;
    else
      return true;
  }
  T* get();
  void reset();
  void reset(T* value);
  T* release();

 private:
  T* _p;
};

template <typename T>
UniquePtr<T>::UniquePtr(T* p) : _p{p} {}

template <typename T>
UniquePtr<T>::~UniquePtr() {
  delete _p;
  _p = nullptr;
}

template <typename T>
T* make_unique(T&& val) {
  return new T{val};
}

template <typename T>
T* UniquePtr<T>::get() {
  return _p;
}

template <typename T>
T& UniquePtr<T>::operator*() {
  return *_p;
}

template <typename T>
T* UniquePtr<T>::operator->() {
  return _p;
}

template <typename T>
void UniquePtr<T>::reset() {
  delete _p;
  _p = nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T* value) {
  delete _p;
  _p = value;
}

template <typename T>
T* UniquePtr<T>::release() {
  T* temp{_p};
  _p = nullptr;
  return temp;
}

/*
Prompt:  please write an example of overloading operator bool in c++ in class
template

Response: template <typename T>
class MyClass {
public:
    // Overload the operator bool to return true if value is non-zero, false
otherwise operator bool() const noexcept { return !value;
    }

private:
    T value;
};


*/
#endif  // UNIQUE_PTR
