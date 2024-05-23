<h1 align="center">
<strong>AUT Advanced Programming Midterm (Spring 2024)</strong>
</h1>

<h2 align="center">
<strong> Exam Duration: 4 hours</strong>
</h2>

Welcome to your midterm assignment, where you will be tasked with implementing a series of smart pointer classes in C++. This project is designed to challenge your understanding of dynamic memory management, object-oriented programming principles, and advanced features of C++.

## Objective

The primary objective of this assignment is to deepen your practical knowledge of managing memory in C++ through the use of smart pointers. By the end of this project, you should be able to design and implement robust classes that handle memory allocation and deallocation automatically, thus helping prevent common issues such as memory leaks and dangling pointers.

## Assignment Overview

You are required to implement the following classes, each serving distinct roles in memory management:

1. **`BaseControlBlock`**: An abstract base class that defines the interface for reference counting mechanisms.
2. **`SharedControlBlock`**: A template class derived from `BaseControlBlock` that manages shared ownership of an object using reference counts.
3. **`WeakControlBlock`**: A template class also derived from `BaseControlBlock`, designed to manage weak ownership without affecting the object's lifetime.
4. **`SharedPtr`**: A template class that implements strong ownership with the help of `SharedControlBlock`, ensuring that the object it manages is deleted when no longer needed.
5. **`WeakPtr`**: A template class that provides weak references to objects managed by `SharedPtr`, allowing temporary access without extending the object’s lifetime.

Your implementation should ensure that all memory management is handled automatically and safely, demonstrating the principles of RAII (Resource Acquisition Is Initialization) to manage resources. 


---

## `BaseControlBlock` Class

The `BaseControlBlock` class serves as an abstract base class for control blocks used in smart pointer implementations. This class encapsulates the functionality necessary for reference counting, which is crucial for managing the life cycle of dynamically allocated objects in C++. By handling both strong and weak reference counts.

### Breakdown of Functions and Member Variables

#### 1. Constructors and Destructors

**Prototype:** (Default Constructor)
```cpp
BaseControlBlock();
``` 
**Purpose:** The default constructor initializes the strong and weak reference counts to zero. This setup is essential for starting the count when a new object is created and managed by a smart pointer.

---

**Prototype:** (Destructor)
```cpp
virtual ~BaseControlBlock();
``` 
**Purpose:** The virtual destructor ensures that derived classes can clean up resources properly. Since it's an abstract class, the destructor must be declared as `default` to indicate that it does nothing by itself but allows for overriding in derived classes.

---

#### 2. Pure Virtual Functions for Managing Strong References

**Prototype:** (Increment Strong Reference Count)
```cpp
virtual void increment_use_count() = 0;
```  
**Purpose:** Increments the strong reference count. This function is critical for managing the lifetime of the managed object. Every time a new smart pointer instance takes ownership of the object, this count is increased to reflect the additional owner.

---

**Prototype:** (Decrement Strong Reference Count)
```cpp
virtual void decrement_use_count() = 0;
```  
**Purpose:** Decrements the strong reference count and potentially manages the deletion of the managed object based on the count. This function is called when a smart pointer releases ownership, such as when it is destructed or reassigned. If the strong count reaches zero, the managed object should be deleted.

---

**Prototype:** (Get Strong Reference Count)
```cpp
virtual int get_use_count() const = 0;
```
**Purpose:** Returns the current strong reference count. This is useful for checking how many smart pointers currently share ownership of the object, which can be critical for debugging and for functions that behave differently depending on ownership status.

---

#### 3. Pure Virtual Functions for Managing Weak References

**Prototype:** (Increment Weak Reference Count)
```cpp
virtual void increment_weak_count() = 0;
```

**Purpose:** Increments the weak reference count. Weak references allow smart pointers to refer to an object without affecting its lifetime, and this function is used to track how many weak pointers are currently referring to the object.

---

**Prototype:** (Decrement Weak Reference Count)
```cpp
virtual void decrement_weak_count() = 0;
```

**Purpose:** Decrements the weak reference count and may manage the deletion of the control block if there are no more references, both strong and weak. This ensures that the control block itself is cleaned up appropriately, preventing memory leaks.

---

**Prototype:** (Get Weak Reference Count)
```cpp
virtual int get_weak_count() const = 0;
```
**Purpose:** Returns the current weak reference count. This information is crucial to determine whether it is safe to delete the control block, as it should only be deleted when both the strong and weak counts are zero.

---

#### 4. Member Variables

**Variable:** `int use_count;`  
**Purpose:** Tracks the number of strong references to the managed object. This count directly influences the lifetime of the object, ensuring it remains allocated as long as there is at least one strong reference.

**Variable:** `int weak_count;`  
**Purpose:** Tracks the number of weak references to the managed object. Unlike `use_count`, `weak_count` does not affect the lifetime of the object but ensures the control block remains until all weak references are also gone.

## `SharedControlBlock` Class

The `SharedControlBlock` class is a template class designed to manage shared ownership of an object through reference counts. It inherits from `BaseControlBlock` and provides mechanisms to manage the lifecycle of objects in conjunction with smart pointers. By using reference counts, the class ensures that objects are properly deleted when they are no longer needed, preventing resource leaks and facilitating robust memory management in C++ applications.

### Breakdown of Functions and Member Variables

#### 1. Constructor

**Prototype:** (Constructor)
```cpp
explicit SharedControlBlock(T* ptr = nullptr);
```
**Purpose:** Initializes the control block with an optional managed object pointer. If a non-null pointer is provided, the control block will manage the object's memory. This constructor sets up the initial state of the object management, ensuring that the control block starts with the proper ownership setup.

---

#### 2. Destructor

**Prototype:** (Destructor)
```cpp
~SharedControlBlock();
```

**Purpose:** Deletes the managed object if no strong references exist. This destructor ensures that the object is cleaned up properly when the reference count drops to zero, preventing memory leaks.

---

#### 3. Strong Reference Management Functions

**Prototype:** (Increment Strong Reference Count)
```cpp
void increment_use_count();
```

**Purpose:** Increments the strong reference count. This method is crucial for managing ownership as new owners (smart pointers) take responsibility for the object.

---

**Prototype:** (Decrement Strong Reference Count)
```cpp
void decrement_use_count();
``` 
**Purpose:** Decrements the strong reference count and deletes the object and potentially this control block if no strong or weak references remain. This method ensures that resources are released in a timely and safe manner when they are no longer needed.

---

**Prototype:** (Get Strong Reference Count)
```cpp
int get_use_count() const;
```
**Purpose:** Returns the current strong reference count, providing a way to query how many active owners exist for the managed object, which is vital for decisions related to resource management.

---

#### 4. Weak Reference Management Functions

**Prototype:** (Increment Weak Reference Count)
```cpp
void increment_weak_count()
```
**Purpose:** Increments the weak reference count. Weak references allow for observation without ownership, and this method tracks such references.

---

**Prototype:** (Decrement Weak Reference Count)
```cpp
void decrement_weak_count();
```  
**Purpose:** Decrements the weak reference count and deletes this control block if no references (strong or weak) remain. It ensures that the control block itself is also cleaned up correctly, preventing any potential memory leak.

---

**Prototype:** (Get Weak Reference Count)
```cpp
int get_weak_count() const;
``` 
**Purpose:** Returns the current weak reference count, which helps in understanding the number of non-owning references to the managed object.

---

#### 5. Accessor for Managed Object

**Prototype:** (Get Managed Object)
```cpp
T* get_managed_object() const;
```
**Purpose:** Returns a pointer to the managed object. This allows smart pointers to access the actual object being managed, facilitating direct interaction with the object's members and methods.

---

#### 6. Member Variable

**Variable:** `T* managed_object;`  
**Purpose:** Stores the pointer to the managed object. This variable is central to the control block's functionality, as it holds the actual object that the smart pointers are managing.

## `WeakControlBlock` Class

The `WeakControlBlock` class is a template class that extends the functionality of `BaseControlBlock` to manage weak ownership of an object. This class plays a crucial role in facilitating weak pointers (`WeakPtr`), which reference an object without affecting its lifetime. By allowing weak ownership, the class enables scenarios where an object can be accessed only if it still exists, thus preventing dangling pointers but not prolonging the object's lifespan unnecessarily.

### Breakdown of Functions and Member Variables

#### 1. Constructor

**Prototype:** (Constructor)
```cpp
explicit WeakControlBlock(SharedControlBlock<T>* sharedBlock = nullptr);
```
**Purpose:** Associates this weak control block with a shared control block, if provided. This constructor allows the weak control block to track and manage the lifecycle of the object alongside strong owners, without influencing the object’s lifetime directly.

---

#### 2. Destructor

**Prototype:** (Destructor)
```cpp
~WeakControlBlock();
``` 
**Purpose:** Decrements the weak count of the associated shared control block upon destruction. This ensures that the weak count accurately reflects the number of current weak references when this block is no longer needed.

---

#### 3. Strong Reference Count Management

**Prototype:** (Increment Strong Reference Count)
```cpp
void increment_use_count();
```
**Purpose:** Increments the strong reference count of the associated object through the shared control block. This function is invoked to temporarily elevate a weak reference to a strong one, ensuring the object remains alive during access.

---

**Prototype:** (Decrement Strong Reference Count)
```cpp
void decrement_use_count();
```
**Purpose:** Decrement the strong reference count of the associated object through the shared control block.

---

**Prototype:** (Get Strong Reference Count)
```cpp
int get_use_count() const;
```
**Purpose:** Returns the current strong reference count from the associated shared control block, providing visibility into how many strong references are currently active.

---

#### 4. Weak Reference Count Management

**Prototype:** (Increment Weak Reference Count)
```cpp
void increment_weak_count();
```
**Purpose:** Increments the weak reference count.
---

**Prototype:** (Decrement Weak Reference Count)
```cpp
void decrement_weak_count();
``` 
**Purpose:** Decrements the weak reference count and may lead to the deletion of this control block if no references (strong or weak) remain. This function is key in managing the lifecycle of the control block itself, ensuring it is deleted when no longer needed.

---

**Prototype:** (Get Weak Reference Count)
```cpp
int get_weak_count() const;
```
**Purpose:** Returns the current weak reference count, which is crucial for determining whether the weak control block can safely be deleted.

---

#### 5. Accessor Functions

**Prototype:** (Get Managed Object)
```cpp
T* get_managed_object() const;
``` 
**Purpose:** Returns a pointer to the managed object, if it is still available. This allows weak pointers to access the object conditionally, based on the object’s existence.

---

**Prototype:** (Get Shared Control Block)
```cpp
SharedControlBlock<T>* get_shared_control_block() const;
```
**Purpose:** Returns a pointer to the associated shared control block. This is useful for weak pointers to elevate to strong pointers if the object is still alive.

---

#### 6. Member Variable

**Variable:** `SharedControlBlock<T>* shared_control_block;`  
**Purpose:** Stores a pointer to the associated shared control block. This variable links the weak control block to the corresponding shared control block, facilitating the management of the object’s lifecycle in tandem with strong references.

## `SharedPtr` Class

The `SharedPtr` class is a template class designed for managing objects through shared ownership in C++. It uses a control block (`SharedControlBlock<T>`) to maintain reference counts, ensuring that an object is automatically deleted when it is no longer needed. This class forms part of a memory management strategy that prevents memory leaks and allows multiple owners for a single object, which is particularly useful in complex systems where object lifetimes are difficult to manage manually.

### Breakdown of Functions and Member Variables

#### 1. Constructors

**Prototype:** (Default Constructor)
```cpp
SharedPtr() noexcept;
```
**Purpose:** Initializes the `SharedPtr` with null pointers for the object and control block. This default state means the pointer does not manage any object initially.

---

**Prototype:** (Constructor from Raw Pointer)
```cpp
explicit SharedPtr(T* ptr);
```
**Purpose:** Constructs a `SharedPtr` from a raw pointer, taking ownership of the object. It initializes a new control block to manage the reference count starting from one.

---

**Prototype:** (Copy Constructor)
**Purpose:** The copy constructor increments the reference count of the existing control block, indicating that another `SharedPtr` is now managing the same object.

---

**Prototype:** (Move Constructor)
**Purpose:** The move constructor transfers ownership from another `SharedPtr` without increasing the reference count. It effectively steals the pointer and control block from the moved-from object, which is then set to null.

---

#### 2. Destructor

**Prototype:** (Destructor)
```cpp
~SharedPtr();
``` 
**Purpose:** Releases ownership of the managed object. If this is the last `SharedPtr` owning the object, it triggers the deletion of the object and the control block through the `release` function.

---

#### 3. Assignment Operators

**Prototype:** (Copy Assignment Operator)
**Purpose:** The copy assignment operator checks for self-assignment, releases the current object if necessary, and then increments the reference count of the control block managed by `other`.

---

**Prototype:** (Move Assignment Operator)
**Purpose:** The move assignment operator transfers ownership from another `SharedPtr`, similar to the move constructor. It ensures any currently managed object is released first.

---

#### 4. Modifiers

**Prototype:** (Reset to Null)
```cpp
void reset() noexcept;
```  
**Purpose:** Resets the `SharedPtr` to manage no object, effectively releasing any current ownership and setting internal pointers to null.

---

**Prototype:** (Reset to New Pointer)
```cpp
void reset(T* new_ptr);
```  
**Purpose:** Resets the `SharedPtr` to manage a new object, releasing any current object and setting up a new control block for the new pointer.

---

#### 5. Accessors

**Prototype:** (Get Raw Pointer)
```cpp
T* get() const noexcept;
```
**Purpose:** Returns the raw pointer to the managed object. This allows direct access to the object `SharedPtr` is managing.

---

**Prototype:** (Get Control Block)
```cpp
SharedControlBlock<T>* get_control_block() const noexcept;
```  
**Purpose:** Returns the control block associated with this `SharedPtr`, providing access to the reference count information.

---

**Prototype:** (Get Use Count)
```cpp
long use_count() const noexcept;
```  
**Purpose:** Returns the number of `SharedPtr` instances managing the same object, which helps in understanding how many copies of the smart pointer exist.

---

**Prototype:** (Check for Uniqueness)
```cpp
bool unique() const noexcept;
```
**Purpose:** Checks if the `SharedPtr` is the sole owner of the object, useful for ensuring that operations affecting the object do not impact other owners.

---

**Prototype:** (Boolean Conversion)
```cpp
explicit operator bool() const noexcept;
```
**Purpose:** Allows the `SharedPtr` to be used in boolean contexts to check if there is a managed object.

---

#### 6. Operators

**Prototype:** (Dereference Operator)
```cpp
T& operator*() const;
```
**Purpose:** Dereferences the stored pointer, providing access to the managed object. This is essential for using `SharedPtr` like a regular pointer.

---

**Prototype:** (Member Access Operator)
```cpp
T* operator->() const noexcept;
```  
**Purpose:** Provides access to the object's members, enabling `SharedPtr` to behave like a regular pointer in accessing member functions and properties.

---

#### 7. Private Member and Helper Function

**Variable:** `T* ptr;`  
**Purpose:** Stores the raw pointer to the managed object.

**

Variable:** `SharedControlBlock<T>* control_block;`  
**Purpose:** Points to the control block that manages the reference counts.

**Prototype:** (Release Resources)
```cpp
void release();
``` 
**Purpose:** A helper function that decrements the reference count and deletes the object and control block if necessary. It encapsulates the logic for safely releasing resources, ensuring correct cleanup.

## `WeakPtr` Class

The `WeakPtr` class is a template class designed for managing a weak reference to an object. Unlike `SharedPtr` that owns the object it points to, `WeakPtr` does not affect the lifetime of the object it references. This type of smart pointer is useful in scenarios where you need to monitor an object without preventing it from being destroyed when all strong references (`SharedPtr` instances) are gone. `WeakPtr` helps prevent dangling pointer issues by providing a way to check the existence of the object before access.

### Breakdown of Functions and Member Variables

#### 1. Constructors

**Prototype:** (Default Constructor)
```cpp
WeakPtr() noexcept;
```
**Purpose:** Initializes the `WeakPtr` with a null control block, indicating that it does not point to any object initially.

---

**Prototype:** (Constructor from SharedPtr)
```cpp
template<typename U>
WeakPtr(const SharedPtr<U>& other) noexcept;
```
**Purpose:** Constructs a `WeakPtr` from a `SharedPtr`, incrementing the weak count of the control block associated with the `SharedPtr`. This allows the `WeakPtr` to reference the same object as the `SharedPtr` without extending its lifetime.

---

**Prototype:** (Copy Constructor)
**Purpose:** The copy constructor increments the weak count of the control block that this `WeakPtr` is referencing, ensuring that the weak reference remains valid as long as the control block exists.

---

**Prototype:** (Move Constructor)
**Purpose:** The move constructor transfers the control block pointer from another `WeakPtr`, effectively taking over the weak reference and setting the original `WeakPtr`'s control block to null.

---

#### 2. Destructor

**Prototype:** (Destructor)
```cpp
~WeakPtr();
``` 
**Purpose:** Decrements the weak count of the control block, potentially leading to its deletion if no more weak or strong references exist. This ensures that resources are cleaned up appropriately.

---

#### 3. Assignment Operators

**Prototype:** (Copy Assignment Operator)
**Purpose:** Assigns one `WeakPtr` to another, handling the increment and decrement of weak counts properly to maintain correct reference management.

---

**Prototype:** (Move Assignment Operator)
**Purpose:** Transfers the weak reference from one `WeakPtr` to another, resetting the original `WeakPtr` and ensuring that the weak count is managed correctly.

---

**Prototype:** (Assignment from SharedPtr)
```cpp
template<typename U>
WeakPtr& operator=(const SharedPtr<U>& other) noexcept;
```  
**Purpose:** Allows a `WeakPtr` to be reassigned to track a different `SharedPtr`, adjusting the weak count as necessary to reflect the new relationship.

---

#### 4. Utility Functions

**Prototype:** (Boolean Conversion)
```cpp
explicit operator bool() const noexcept;
```
**Purpose:** Checks if the object managed by the `WeakPtr` still exists (i.e., it has not been deleted). Returns true if the object is still alive, false otherwise.

---

**Prototype:** (Reset WeakPtr)
```cpp
void reset() noexcept;
``` 
**Purpose:** Clears the control block of the `WeakPtr`, resetting it to a null state and decrementing any existing weak count.

---

**Prototype:** (Check if Expired)
```cpp
bool expired() const noexcept;
``` 
**Purpose:** Returns true if the object has been deleted (i.e., the strong count has dropped to zero), indicating that the `WeakPtr` no longer has a valid object to reference.

---

**Prototype:** (Get Use Count)
```cpp
long use_count() const noexcept;
``` 
**Purpose:** Provides the number of strong references (`SharedPtr` instances) managing the same object, which can be useful for diagnostics and managing object lifecycle.

---

**Prototype:** (Lock to SharedPtr)
```cpp
SharedPtr<T> lock() const noexcept;
``` 
**Purpose:** Attempts to convert the `WeakPtr` into a `SharedPtr`. If the object is still alive, this returns a valid `SharedPtr` managing the object; if not, it returns an empty `SharedPtr`.

---

#### 5. Member Variable

**Variable:** `WeakControlBlock<T>* control_block;`  
**Purpose:** Holds the pointer to the weak control block that manages the reference counts and object existence checks. This is the central component that links the `WeakPtr` to the actual object and its lifecycle.

---

## **Final Step: How To Test Your Program**

If you want to debug your code, set the `if` statement to `true`. This will allow you to place your debugging code in the designated section. Once you're done with the debugging process, remember to set the `if` statement back to `false` to test your program using the provided `unit-test.cpp`.

Furthermore, whatever code you write should be implemented in the `BaseControlBlock.h`, `SharedControlBlock.h`, `WeakControlBlock.h`, `SharedPtr.h` and `WeakPtr.h` files. Please refrain from making any changes to other files in the project.

```cpp
#include <iostream>
#include <gtest/gtest.h>

#include "BaseControlBlock.h"
#include "SharedControlBlock.h"
#include "WeakControlBlock.h"
#include "SharedPtr.h"
#include "WeakPtr.h"

int main(int argc, char **argv)
{
    if (true) // Set to false to run unit-tests
    {
        // Debug section: Place your debugging code here
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}
```

**Best Regards, [Hamidi](https://github.com/smhamidi)**
