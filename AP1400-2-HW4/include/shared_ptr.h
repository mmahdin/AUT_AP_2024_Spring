#ifndef SHARED_PTR
#define SHARED_PTR

#include <iostream>

template <typename T>
class SharedPtr {
 public:
  SharedPtr(T* ptr);
  SharedPtr();
  ~SharedPtr();
  SharedPtr(const SharedPtr& other);
  SharedPtr<T>& operator=(const SharedPtr& other);
  unsigned getn() { return *cnt; }
  unsigned use_count() {
    if (cnt != nullptr)
      return *cnt;
    else
      return 0;
  }
  operator bool() {
    if (_p == nullptr)
      return false;
    else
      return true;
  }
  T* get();
  T& operator*();
  T* operator->();
  void reset();
  void reset(T* value);

 private:
  T* _p;
  unsigned* cnt;
  void release() {
    if (_p) {
      if (cnt) {
        if (--(*cnt) == 0) {
          delete _p;
          delete cnt;
        }
      }
      _p = nullptr;
      cnt = nullptr;
    }
  }
};

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) : _p{ptr}, cnt{new unsigned{1}} {
  if (ptr == nullptr) *cnt = 0;
}

template <typename T>
T* make_shared(T&& value) {
  return new T{value};
}

template <typename T>
SharedPtr<T>::SharedPtr() : _p{nullptr}, cnt{new unsigned{0}} {}

template <typename T>
SharedPtr<T>::~SharedPtr() {
  release();
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) : _p{other._p}, cnt{other.cnt} {
  if (_p) ++(*cnt);
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
  if (this != &other) {
    // release();
    cnt = other.cnt;
    if (_p) ++(*cnt);
    _p = other._p;
  }
  return *this;
}

template <typename T>
T* SharedPtr<T>::get() {
  if (_p != nullptr)
    return _p;
  else
    return nullptr;
}

template <typename T>
T& SharedPtr<T>::operator*() {
  return *_p;
}

template <typename T>
T* SharedPtr<T>::operator->() {
  return _p;
}

template <typename T>
void SharedPtr<T>::reset() {
  release();
}

template <typename T>
void SharedPtr<T>::reset(T* value) {
  release();
  _p = value;
  cnt = new unsigned{1};

  if ((*cnt) == 0)
    ++(*cnt);
  else if (cnt != nullptr)
    cnt = new unsigned{1};
}

#endif  // SHARED_PTR