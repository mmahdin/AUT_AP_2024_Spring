#ifndef WEAK_PTR_H
#define WEAK_PTR_H

#include "SharedPtr.h"
#include "WeakControlBlock.h"

template <typename T>

class WeakPtr {
 public:
  WeakPtr() noexcept;
  WeakPtr(const SharedPtr<T>& other) noexcept;
  WeakPtr(const WeakPtr& other);
  WeakPtr(WeakPtr&& other);
  ~WeakPtr();

  WeakPtr<T>& operator=(const WeakPtr& other);
  WeakPtr<T>& operator=(WeakPtr&& other);

  WeakPtr& operator=(const SharedPtr<T>& other) noexcept;

  explicit operator bool() const noexcept {
    if (control_block == nullptr) return false;
    if (control_block->get_shared_control_block() == nullptr) return false;
    return true;
  }

  void reset() noexcept;
  bool expired() const noexcept;
  long use_count() const noexcept;
  SharedPtr<T> lock() const noexcept;

 private:
  WeakControlBlock<T>* control_block;
};

template <typename T>
WeakPtr<T>::WeakPtr() noexcept : control_block{new WeakControlBlock<T>{}} {}

template <typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& other) noexcept {
  control_block = new WeakControlBlock<T>{other.get_control_block()};
}

// copy
template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& other) {
  control_block = other.control_block;
  control_block->increment_weak_count();
}

// move
template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr&& other) {
  control_block = other.control_block;
  other.control_block = nullptr;
}

template <typename T>
WeakPtr<T>::~WeakPtr() {}

template <typename T>
bool WeakPtr<T>::expired() const noexcept {
  if (control_block == nullptr) {
    return 1;
  } else if (control_block->get_shared_control_block() == nullptr) {
    return 1;
  } else if (control_block->get_use_count() == 0) {
    return 1;
  } else
    return 0;
}

template <typename T>
long WeakPtr<T>::use_count() const noexcept {
  if (control_block == nullptr) return 0;
  return control_block->get_use_count();
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& other) {
  control_block = other.control_block;
  control_block->increment_weak_count();
  return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr&& other) {
  control_block = other.control_block;
  other.control_block = nullptr;
  return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const SharedPtr<T>& other) noexcept {
  control_block = new WeakControlBlock<T>{other.get_control_block()};
  return *this;
}

template <typename T>
void WeakPtr<T>::reset() noexcept {
  control_block->decrement_weak_count();
  control_block = nullptr;
}

template <typename T>
SharedPtr<T> WeakPtr<T>::lock() const noexcept {
  if (control_block) {
    if (control_block->get_use_count() > 0) {
      SharedPtr<T> temp{
          control_block->get_shared_control_block()->get_managed_object()};
      for (int i; i < control_block->get_use_count(); i++) {
        temp.get_control_block()->increment_use_count();
      }
      control_block->increment_use_count();
      return temp;
    }
  }
  SharedPtr<T> temp2;
  return temp2;
}

#endif  // WEAK_PTR_H
