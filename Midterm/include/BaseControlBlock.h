#ifndef BASE_CONTROL_BLOCK_H
#define BASE_CONTROL_BLOCK_H

/**
 * @brief Abstract base class for control blocks, supporting reference counting mechanisms.
 */
class BaseControlBlock {
public:
    // Default constructor initializes reference counts to zero.
    BaseControlBlock() : use_count(0), weak_count(0) {}

    // Virtual destructor for cleanup in derived classes.
    virtual ~BaseControlBlock() = default;

    // Increments the strong reference count.
    virtual void increment_use_count() = 0;

    // Decrements the strong reference count and manages object deletion.
    virtual void decrement_use_count() = 0;

    // Returns the current strong reference count.
    virtual int get_use_count() const = 0;

    // Increments the weak reference count.
    virtual void increment_weak_count() = 0;

    // Decrements the weak reference count and manages control block deletion.
    virtual void decrement_weak_count() = 0;

    // Returns the current weak reference count.
    virtual int get_weak_count() const = 0;

protected:
    int use_count;  // Number of strong references.
    int weak_count;  // Number of weak references.
};

#endif // BASE_CONTROL_BLOCK_H