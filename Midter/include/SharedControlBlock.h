#ifndef SHARED_CONTROL_BLOCK_H
#define SHARED_CONTROL_BLOCK_H

#include "BaseControlBlock.h"

template <typename T>
class SharedControlBlock : public BaseControlBlock {
 public:
  explicit SharedControlBlock(T* ptr = nullptr);
  ~SharedControlBlock();
  void increment_use_count() override;
  void decrement_use_count() override;
  int get_use_count() const override;
  void increment_weak_count() override;
  void decrement_weak_count() override;
  int get_weak_count() const override;
  T* get_managed_object() const;

 private:
  int use_count;
  int weak_count;
  T* managed_object;
};

template <typename T>
SharedControlBlock<T>::SharedControlBlock(T* ptr)
    : use_count{0}, weak_count{0}, managed_object{ptr} {
  if (ptr) {
    use_count++;
    weak_count++;
  }
}

template <typename T>
SharedControlBlock<T>::~SharedControlBlock() {}

template <typename T>
void SharedControlBlock<T>::increment_use_count() {
  use_count++;
}

template <typename T>
void SharedControlBlock<T>::decrement_use_count() {
  use_count--;
}

template <typename T>
int SharedControlBlock<T>::get_use_count() const {
  return use_count;
}

template <typename T>
void SharedControlBlock<T>::increment_weak_count() {
  weak_count++;
}

template <typename T>
void SharedControlBlock<T>::decrement_weak_count() {
  weak_count--;
}

template <typename T>
int SharedControlBlock<T>::get_weak_count() const {
  return weak_count;
}

template <typename T>
T* SharedControlBlock<T>::get_managed_object() const {
  return managed_object;
}

#endif  // SHARED_CONTROL_BLOCK_H
