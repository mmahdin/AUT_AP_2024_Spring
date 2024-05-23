#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <exception>
#include <iostream>

#include "SharedControlBlock.h"
// class SharedControlBlock;

template <typename T>
class SharedPtr {
  friend class SharedControlBlock<T>;

 public:
  SharedPtr() noexcept;
  explicit SharedPtr(T* ptr);
  SharedPtr(const SharedPtr& other);
  SharedPtr(SharedPtr&& other);
  ~SharedPtr();

  SharedPtr<T>& operator=(const SharedPtr& other);
  SharedPtr<T>& operator=(SharedPtr&& other);

  void reset() noexcept;
  void reset(T* new_ptr);
  T* get() const noexcept;
  SharedControlBlock<T>* get_control_block() const noexcept;
  long use_count() const noexcept;
  bool unique() const noexcept;
  explicit operator bool() const noexcept {
    if (ptr == nullptr)
      return false;
    else
      return true;
  }
  T& operator*() const;
  T* operator->() const;

 private:
  T* ptr;
  SharedControlBlock<T>* control_block;

  void release() {
    if (ptr) {
      if (control_block) {
        control_block->decrement_use_count();
        // control_block->decrement_weak_count();

        if (control_block->get_use_count() == 0) {
          delete ptr;
          //   delete control_block;
        }
        ptr = nullptr;
        control_block = nullptr;
      }
    }
  }
};

template <typename T>
SharedPtr<T>::SharedPtr() noexcept
    : ptr{nullptr}, control_block{new SharedControlBlock<T>{ptr}} {}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr)
    : ptr{ptr}, control_block{new SharedControlBlock<T>{ptr}} {}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other)
    : ptr{other.ptr}, control_block{other.control_block} {
  control_block->increment_use_count();
  control_block->increment_weak_count();
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other)
    : ptr{other.ptr}, control_block{other.control_block} {
  other.ptr = nullptr;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
  release();
}

template <typename T>
T* SharedPtr<T>::get() const noexcept {
  return ptr;
}

template <typename T>
long SharedPtr<T>::use_count() const noexcept {
  if (control_block)
    return control_block->get_use_count();
  else
    return 0;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
  if (this != &other) {
    control_block = other.control_block;
    control_block->increment_use_count();
    ptr = other.ptr;
  }
  return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) {
  if (this != &other) {
    control_block = other.control_block;
    ptr = other.ptr;
    other.ptr = nullptr;
  }
  return *this;
}

template <typename T>
void SharedPtr<T>::reset() noexcept {
  release();
  control_block = nullptr;
}

template <typename T>
void SharedPtr<T>::reset(T* new_ptr) {
  release();
  ptr = new_ptr;
  control_block = new SharedControlBlock<T>{ptr};
}

template <typename T>
bool SharedPtr<T>::unique() const noexcept {
  if (control_block->get_use_count() == 1)
    return 1;
  else
    return 0;
}

template <typename T>
T& SharedPtr<T>::operator*() const {
  if (ptr)
    return *ptr;
  else
    throw std::invalid_argument("nulptr");
}

template <typename T>
T* SharedPtr<T>::operator->() const {
  if (ptr)
    return ptr;
  else
    throw std::invalid_argument("nulptr");
}

template <typename T>
SharedControlBlock<T>* SharedPtr<T>::get_control_block() const noexcept {
  return control_block;
}
#endif  // SHARED_PTR_H
