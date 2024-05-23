#ifndef WEAK_CONTROL_BLOCK_H
#define WEAK_CONTROL_BLOCK_H

#include "BaseControlBlock.h"
#include "SharedControlBlock.h"

template <typename T>
class WeakControlBlock : public BaseControlBlock {
 public:
  explicit WeakControlBlock(SharedControlBlock<T>* sharedBlock = nullptr);
  ~WeakControlBlock();
  void increment_use_count() override;
  void decrement_use_count() override;
  int get_use_count() const override;
  void increment_weak_count() override;
  void decrement_weak_count() override;
  int get_weak_count() const override;
  T* get_managed_object() const;
  SharedControlBlock<T>* get_shared_control_block() const;

 private:
  SharedControlBlock<T>* shared_control_block;
};

template <typename T>
WeakControlBlock<T>::WeakControlBlock(SharedControlBlock<T>* sharedBlock)
    : shared_control_block{sharedBlock} {}

template <typename T>
WeakControlBlock<T>::~WeakControlBlock() {}

template <typename T>
void WeakControlBlock<T>::increment_use_count() {
  shared_control_block->increment_use_count();
}

template <typename T>
void WeakControlBlock<T>::decrement_use_count() {
  shared_control_block->decrement_use_count();
}

template <typename T>
int WeakControlBlock<T>::get_use_count() const {
  return shared_control_block->get_use_count();
}

template <typename T>
void WeakControlBlock<T>::increment_weak_count() {
  shared_control_block->increment_weak_count();
}

template <typename T>
void WeakControlBlock<T>::decrement_weak_count() {
  shared_control_block->decrement_weak_count();
}

template <typename T>
int WeakControlBlock<T>::get_weak_count() const {
  return shared_control_block->get_weak_count();
}

template <typename T>
SharedControlBlock<T>* WeakControlBlock<T>::get_shared_control_block() const {
  return shared_control_block;
}

#endif  // WEAK_CONTROL_BLOCK_H
