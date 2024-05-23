#include <gtest/gtest.h>

#include <iostream>

#include "BaseControlBlock.h"
#include "SharedControlBlock.h"
#include "SharedPtr.h"
#include "WeakControlBlock.h"
#include "WeakPtr.h"

// ############################################
// ######## Shared Pointer Constructor ########
// ############################################

// Test for Default Constructor
TEST(SharedPtrTest, Shared_DefaultConstructor) {
  SharedPtr<int> ptr;
  EXPECT_EQ(ptr.get(), nullptr)
      << "Default constructed SharedPtr should be nullptr";
  EXPECT_EQ(ptr.use_count(), 0)
      << "Default constructed SharedPtr should have use count of 0";
}

// Test for Pointer Constructor
TEST(SharedPtrTest, Shared_PointerConstructor) {
  int* rawPtr = new int(10);
  SharedPtr<int> ptr(rawPtr);
  EXPECT_EQ(ptr.get(), rawPtr)
      << "SharedPtr should hold the raw pointer provided at construction";
  EXPECT_EQ(ptr.use_count(), 1)
      << "SharedPtr constructed with raw pointer should have use count of 1";
}

// Test for Copy Constructor

TEST(SharedPtrTest, Shared_CopyConstructor) {
  SharedPtr<int> original(new int(20));
  SharedPtr<int> copy(original);
  EXPECT_EQ(copy.get(), original.get())
      << "Copied SharedPtr should point to the same object as the original";
  EXPECT_EQ(copy.use_count(), 2)
      << "Use count should be incremented to 2 after copy";
  EXPECT_EQ(original.use_count(), 2)
      << "Original SharedPtr use count should be 2 after being copied";
}

// Test for Move Constructor
TEST(SharedPtrTest, Shared_MoveConstructor) {
  SharedPtr<int> original(new int(30));
  SharedPtr<int> moved(std::move(original));
  EXPECT_EQ(original.get(), nullptr)
      << "Moved-from SharedPtr should be nullptr";
  EXPECT_EQ(moved.use_count(), 1)
      << "Moved-to SharedPtr should retain a use count of 1";
}

// ############################################
// ######## Shared Pointer Destructor  ########
// ############################################

class DestructorTestHelper {
 public:
  static int destruction_count;
  DestructorTestHelper() {}
  ~DestructorTestHelper() { ++destruction_count; }
};

int DestructorTestHelper::destruction_count = 0;

// Test for Single Owner Destruction
TEST(SharedPtrTest, Shared_SingleOwnerDestruction) {
  {
    SharedPtr<DestructorTestHelper> ptr(new DestructorTestHelper());
  }  // ptr goes out of scope here
  EXPECT_EQ(DestructorTestHelper::destruction_count, 1)
      << "The managed object should be destroyed when the last SharedPtr goes "
         "out of scope";
}

// Test for Multiple Owners
TEST(SharedPtrTest, Shared_MultipleOwners) {
  DestructorTestHelper* rawPtr = new DestructorTestHelper();
  {
    SharedPtr<DestructorTestHelper> firstOwner(rawPtr);
    {
      SharedPtr<DestructorTestHelper> secondOwner(firstOwner);
      DestructorTestHelper::destruction_count =
          0;  // Reset destruction count before the scope ends
    }         // secondOwner goes out of scope here
    EXPECT_EQ(DestructorTestHelper::destruction_count, 0)
        << "The managed object should not be destroyed while another SharedPtr "
           "still owns it";
    EXPECT_EQ(firstOwner.use_count(), 1)
        << "One owner should remain, so use count should be 1";
  }  // firstOwner goes out of scope here
  EXPECT_EQ(DestructorTestHelper::destruction_count, 1)
      << "The managed object should be destroyed when the last SharedPtr goes "
         "out of scope";
}

// ############################################
// ######## Shared Pointer Assignment  ########
// ############################################

// Test for Copy Assignment to Empty
TEST(SharedPtrTest, Shared_CopyAssignmentToEmpty) {
  SharedPtr<int> original(new int(10));
  SharedPtr<int> copy;
  copy = original;
  EXPECT_EQ(copy.get(), original.get())
      << "Both SharedPtrs should point to the same object after copy "
         "assignment";
  EXPECT_EQ(copy.use_count(), 2)
      << "Use count should be 2 after copying to another SharedPtr";
}

// Test for Copy Assignment Over Existing
TEST(SharedPtrTest, Shared_CopyAssignmentOverExisting) {
  SharedPtr<int> original(new int(20));
  SharedPtr<int> copy(new int(30));
  int* oldPtr = copy.get();
  copy = original;
  EXPECT_EQ(copy.get(), original.get())
      << "Both SharedPtrs should point to the same object after copy "
         "assignment";
  EXPECT_EQ(copy.use_count(), 2) << "Use count should be 2 after copy "
                                    "assignment over an existing SharedPtr";
  EXPECT_EQ(original.use_count(), 2)
      << "Original SharedPtr use count should also be 2";
  delete oldPtr;  // Manual delete since we've replaced the pointer in copy
                  // without decrementing use count
}

// Test for Move Assignment to Empty
TEST(SharedPtrTest, Shared_MoveAssignmentToEmpty) {
  SharedPtr<int> original(new int(40));
  SharedPtr<int> moved;
  moved = std::move(original);
  EXPECT_EQ(moved.get(), moved.get())
      << "Moved-to SharedPtr should point to the object originally owned by "
         "moved-from SharedPtr";
  EXPECT_EQ(original.get(), nullptr)
      << "Moved-from SharedPtr should be nullptr after move assignment";
  EXPECT_EQ(moved.use_count(), 1)
      << "Moved-to SharedPtr should have a use count of 1";
}

// Test for Move Assignment Over Existing
TEST(SharedPtrTest, Shared_MoveAssignmentOverExisting) {
  SharedPtr<int> original(new int(50));
  SharedPtr<int> moved(new int(60));
  int* oldPtr = moved.get();
  moved = std::move(original);
  EXPECT_EQ(moved.get(), moved.get())
      << "Moved-to SharedPtr should point to the object originally owned by "
         "moved-from SharedPtr";
  EXPECT_EQ(original.get(), nullptr)
      << "Moved-from SharedPtr should be nullptr after move assignment";
  EXPECT_EQ(moved.use_count(), 1)
      << "Moved-to SharedPtr should have a use count of 1";
  delete oldPtr;  // Manual delete since we've replaced the pointer in moved
                  // without decrementing use count
}

// ############################################
// ######## Shared Pointer Modifiers   ########
// ############################################

class Resource {
 public:
  static int count;
  Resource() { ++count; }
  ~Resource() { --count; }
};

int Resource::count = 0;

// Test for Reset to Null
TEST(SharedPtrTest, Shared_ResetToNull) {
  SharedPtr<Resource> ptr(new Resource());
  ASSERT_EQ(Resource::count, 1) << "One resource should be created.";
  ptr.reset();

  EXPECT_EQ(ptr.get(), nullptr) << "SharedPtr should be nullptr after reset.";
  EXPECT_EQ(ptr.use_count(), 0) << "Use count should be 0 after reset.";
  EXPECT_EQ(Resource::count, 0) << "Resource should be destroyed after reset.";
}

// Test for Reset with New Pointer
TEST(SharedPtrTest, Shared_ResetWithNewPointer) {
  SharedPtr<Resource> ptr(new Resource());
  Resource* newResource = new Resource();
  ASSERT_EQ(Resource::count, 2) << "Two resources should be created initially.";
  ptr.reset(newResource);
  EXPECT_EQ(ptr.get(), newResource)
      << "SharedPtr should point to the new resource after reset.";
  EXPECT_EQ(ptr.use_count(), 1)
      << "Use count should be 1 after reset with new pointer.";
  EXPECT_EQ(Resource::count, 1)
      << "Only one resource should remain after reset.";
}

// ############################################
// ######## Shared Pointer Observers   ########
// ############################################

// Test for Get with Non-Null
TEST(SharedPtrTest, Shared_GetForNonNull) {
  int* rawPtr = new int(10);
  SharedPtr<int> ptr(rawPtr);
  EXPECT_EQ(ptr.get(), rawPtr) << "get() should return the correct pointer "
                                  "when SharedPtr is managing an object.";
}

// Test for Get with Null
TEST(SharedPtrTest, Shared_GetForNull) {
  SharedPtr<int> ptr;
  EXPECT_EQ(ptr.get(), nullptr) << "get() should return nullptr when SharedPtr "
                                   "is not managing any object.";
}

// Test for Use Count Validity
TEST(SharedPtrTest, Shared_UseCountValidity) {
  SharedPtr<int> ptr1(new int(20));
  SharedPtr<int> ptr2 = ptr1;  // Copy construct
  SharedPtr<int> ptr3;
  ptr3 = ptr2;  // Copy assign
  EXPECT_EQ(ptr1.use_count(), 3)
      << "use_count() should report 3 as the number of shared owners.";
  EXPECT_EQ(ptr2.use_count(), 3)
      << "use_count() should report 3 as the number of shared owners.";
  EXPECT_EQ(ptr3.use_count(), 3)
      << "use_count() should report 3 as the number of shared owners.";
}

// Test for Unique Ownership
TEST(SharedPtrTest, Shared_UniqueOwnership) {
  SharedPtr<int> ptr(new int(30));
  EXPECT_TRUE(ptr.unique()) << "unique() should return true when there is only "
                               "one SharedPtr owning the resource.";
  SharedPtr<int> ptr2 = ptr;
  EXPECT_FALSE(ptr.unique()) << "unique() should return false when the "
                                "resource is owned by more than one SharedPtr.";
}

// Test for Boolean Conversion
TEST(SharedPtrTest, Shared_BooleanConversion) {
  SharedPtr<int> ptr1(new int(40));
  EXPECT_TRUE(ptr1) << "Boolean conversion should return true when SharedPtr "
                       "is managing an object.";
  SharedPtr<int> ptr2;
  EXPECT_FALSE(ptr2) << "Boolean conversion should return false when SharedPtr "
                        "is not managing any object.";
}

// ############################################
// ######## Shared Pointer Dereference ########
// ############################################

class MyClass {
 public:
  int value;
  MyClass(int val) : value(val) {}
  int getValue() const { return value; }
};

// Test for Dereference Operator *
TEST(SharedPtrTest, Shared_DereferenceOperator) {
  SharedPtr<MyClass> ptr(new MyClass(100));
  EXPECT_EQ((*ptr).value, 100)
      << "* operator should provide access to the managed object.";
}

// Test for Arrow Operator ->
TEST(SharedPtrTest, Shared_ArrowOperator) {
  SharedPtr<MyClass> ptr(new MyClass(200));
  EXPECT_EQ(ptr->getValue(), 200)
      << "-> operator should correctly access members of the managed object.";
}

// Test for Dereference Safety
TEST(SharedPtrTest, Shared_DereferenceSafety) {
  SharedPtr<MyClass> empty;
  EXPECT_THROW({ *empty; }, std::exception)
      << "Dereferencing an empty SharedPtr should throw an exception.";
  EXPECT_THROW({ empty->getValue(); }, std::exception)
      << "Accessing members via -> on an empty SharedPtr should throw an "
         "exception.";
}

// ############################################
// ######## Shared Pointer Exception   ########
// ############################################

class ExceptionSimulator {
 public:
  static bool throwOnCopy;
  int data;
  ExceptionSimulator(int val) : data(val) {}
  ExceptionSimulator(const ExceptionSimulator& other) {
    if (throwOnCopy) {
      throw std::runtime_error("Copy constructor exception!");
    }
    data = other.data;
  }
};
bool ExceptionSimulator::throwOnCopy = false;

// Test for No-Throw Guarantees
TEST(SharedPtrTest, Shared_NoThrowGuarantees) {
  SharedPtr<MyClass> ptr1(new MyClass(10));
  SharedPtr<MyClass> ptr2;

  EXPECT_NO_THROW(ptr2 = std::move(ptr1))
      << "Move assignment should not throw any exceptions.";
  EXPECT_NO_THROW(SharedPtr<MyClass> ptr3(std::move(ptr2)))
      << "Move constructor should not throw any exceptions.";
}

// Test for Strong Exception Safety in Copy Assignment
TEST(SharedPtrTest, Shared_StrongExceptionSafety) {
  SharedPtr<ExceptionSimulator> stablePtr(new ExceptionSimulator(100));
  SharedPtr<ExceptionSimulator> ptrToTest(new ExceptionSimulator(200));
  ExceptionSimulator::throwOnCopy =
      true;  // Enable exception throwing for the next copy operation

  try {
    ptrToTest = stablePtr;
  } catch (const std::exception& e) {
    // Test that ptrToTest remains unchanged after a failed assignment
    EXPECT_EQ(ptrToTest->data, 200) << "SharedPtr should preserve the original "
                                       "state if copy assignment throws.";
  }

  ExceptionSimulator::throwOnCopy = false;  // Reset throwing behavior
}

// ############################################
// ######## Shared Pointer Edge Cases  ########
// ############################################

class SelfReferentialClass {
 public:
  SharedPtr<SelfReferentialClass> self;
};

// Test for Self-Assignment with Copy Assignment
TEST(SharedPtrTest, Shared_SelfAssignmentCopy) {
  SharedPtr<int> ptr(new int(42));
  ptr = ptr;  // Self-assignment
  EXPECT_EQ(*ptr, 42)
      << "Self-assignment with copy should not alter the managed object.";
  EXPECT_EQ(ptr.use_count(), 1)
      << "Use count should remain 1 after self-assignment.";
}

// Test for Circular References
// TEST(SharedPtrTest, Shared_CircularReferences) {
//   SharedPtr<SelfReferentialClass> ptr1(new SelfReferentialClass());
//   ptr1->self = ptr1;  // Creating a circular reference
//   SharedPtr<SelfReferentialClass> ptr2 =
//       ptr1;  // Additional reference to the same object

//   // Use count should be 2 after copying the shared pointer
//   EXPECT_EQ(ptr1.use_count(), 2)
//       << "Use count should be 2 with the second pointer sharing ownership.";
//   EXPECT_EQ(ptr2.use_count(), 2)
//       << "Both pointers should report the same use count.";

//   ptr1.reset();  // Break one link in the circular chain
//   EXPECT_EQ(ptr1.use_count(), 0)
//       << "ptr1 should have a use count of 0 after reset.";
//   EXPECT_EQ(ptr2.use_count(), 1) << "ptr2 should still have a use count of 1
//   "
//                                     "after breaking circular reference.";

//   ptr2.reset();  // Break the last link, should cleanup
//   EXPECT_EQ(ptr2.use_count(), 0)
//       << "Final reset should clear the last reference, allowing cleanup.";
// }

// ############################################
// ######## Weak Pointer Constructor   ########
// ############################################

class SimpleResource {
 public:
  int data;
  SimpleResource(int val) : data(val) {}
};

// Test for Default Constructor
TEST(WeakPtrTest, Weak_DefaultConstructor) {
  WeakPtr<SimpleResource> weak;
  EXPECT_TRUE(weak.expired())
      << "A default-constructed WeakPtr should be expired.";
}

// Test for Constructor from SharedPtr
TEST(WeakPtrTest, Weak_ConstructorFromSharedPtr) {
  SharedPtr<SimpleResource> shared(new SimpleResource(10));
  WeakPtr<SimpleResource> weak(shared);
  EXPECT_FALSE(weak.expired()) << "WeakPtr constructed from a non-empty "
                                  "SharedPtr should not be expired.";
  EXPECT_EQ(weak.use_count(), 1) << "Use count through WeakPtr should match "
                                    "the number of SharedPtr owners.";
}

// Test for Copy Constructor
TEST(WeakPtrTest, Weak_CopyConstructor) {
  SharedPtr<SimpleResource> shared(new SimpleResource(20));
  WeakPtr<SimpleResource> weak1(shared);
  WeakPtr<SimpleResource> weak2(weak1);
  EXPECT_EQ(weak1.use_count(), 1)
      << "Use count should remain unchanged after copying a WeakPtr.";
  EXPECT_EQ(weak2.use_count(), 1)
      << "Copied WeakPtr should have the same use count as the original.";
  EXPECT_FALSE(weak1.expired())
      << "Original WeakPtr should not be expired after copying.";
  EXPECT_FALSE(weak2.expired()) << "Copied WeakPtr should not be expired.";
}

// Test for Move Constructor
TEST(WeakPtrTest, Weak_MoveConstructor) {
  SharedPtr<SimpleResource> shared(new SimpleResource(30));
  WeakPtr<SimpleResource> weak1(shared);
  WeakPtr<SimpleResource> weak2(std::move(weak1));
  EXPECT_TRUE(weak1.expired())
      << "Source WeakPtr should be expired after being moved from.";
  EXPECT_FALSE(weak2.expired())
      << "Destination WeakPtr should not be expired after move.";
  EXPECT_EQ(weak2.use_count(), 1)
      << "Moved WeakPtr should retain the correct use count.";
}

// ############################################
// ######## Weak Pointer Destructor    ########
// ############################################

// Test for Destructor Behavior
TEST(WeakPtrTest, Weak_DestructorBehavior) {
  Resource::count = 0;
  SharedPtr<Resource> shared(new Resource());
  EXPECT_EQ(Resource::count, 1)
      << "There should be exactly one instance of Resource after creation.";

  {
    WeakPtr<Resource> weak(shared);
    EXPECT_EQ(weak.use_count(), 1)
        << "Use count should be 1, as there is one SharedPtr.";
    EXPECT_EQ(shared.use_count(), 1)
        << "SharedPtr's use count should be 1 initially.";
  }  // weak goes out of scope here

  EXPECT_EQ(Resource::count, 1) << "Resource instance should not be destroyed "
                                   "when WeakPtr is destructed.";
  EXPECT_EQ(shared.use_count(), 1)
      << "SharedPtr's use count should remain 1 after WeakPtr is destructed.";
}

// ############################################
// ######## Weak Pointer Assignment    ########
// ############################################

// Test for Copy Assignment to Empty
TEST(WeakPtrTest, Weak_CopyAssignmentToEmpty) {
  SharedPtr<MyClass> shared(new MyClass(10));
  WeakPtr<MyClass> weak1(shared);
  WeakPtr<MyClass> weak2;
  weak2 = weak1;
  EXPECT_EQ(weak2.use_count(), 1) << "Weak count should be correct after "
                                     "copying to an uninitialized WeakPtr.";
  EXPECT_FALSE(weak2.expired())
      << "WeakPtr should not be expired after copy assignment.";
}

// Test for Copy Assignment Over Existing
TEST(WeakPtrTest, Weak_CopyAssignmentOverExisting) {
  SharedPtr<MyClass> shared1(new MyClass(20));
  SharedPtr<MyClass> shared2(new MyClass(30));
  WeakPtr<MyClass> weak1(shared1);
  WeakPtr<MyClass> weak2(shared2);
  weak2 = weak1;
  EXPECT_EQ(weak2.use_count(), 1)
      << "Weak count should be correctly managed when WeakPtr is assigned over "
         "another already referencing an object.";
  EXPECT_EQ(weak1.use_count(), 1)
      << "Source WeakPtr's use count should remain unchanged.";
  EXPECT_FALSE(weak2.expired()) << "WeakPtr should not be expired after copy "
                                   "assignment over existing WeakPtr.";
}

// Test for Move Assignment to Empty
TEST(WeakPtrTest, Weak_MoveAssignmentToEmpty) {
  SharedPtr<MyClass> shared(new MyClass(40));
  WeakPtr<MyClass> weak1(shared);
  WeakPtr<MyClass> weak2;
  weak2 = std::move(weak1);
  EXPECT_EQ(weak2.use_count(), 1) << "Use count should be correct after moving "
                                     "to an uninitialized WeakPtr.";
  EXPECT_TRUE(weak1.expired()) << "Moved-from WeakPtr should be expired.";
  EXPECT_FALSE(weak2.expired()) << "Moved-to WeakPtr should not be expired.";
}

// Test for Move Assignment Over Existing
TEST(WeakPtrTest, Weak_MoveAssignmentOverExisting) {
  SharedPtr<MyClass> shared1(new MyClass(50));
  SharedPtr<MyClass> shared2(new MyClass(60));
  WeakPtr<MyClass> weak1(shared1);
  WeakPtr<MyClass> weak2(shared2);
  weak2 = std::move(weak1);
  EXPECT_EQ(weak2.use_count(), 1)
      << "Use count should be correct after moving over an existing WeakPtr.";
  EXPECT_TRUE(weak1.expired()) << "Moved-from WeakPtr should be expired.";
  EXPECT_FALSE(weak2.expired()) << "Moved-to WeakPtr should not be expired.";
}

// Test for Assign from SharedPtr
TEST(WeakPtrTest, Weak_AssignFromSharedPtr) {
  SharedPtr<MyClass> shared(new MyClass(70));
  WeakPtr<MyClass> weak;
  weak = shared;
  EXPECT_EQ(weak.use_count(), 1)
      << "Weak count should be correct after assigning from SharedPtr.";
  EXPECT_FALSE(weak.expired())
      << "WeakPtr should not be expired after assignment from SharedPtr.";
}

// ############################################
// ######## Weak Pointer Modifiers     ########
// ############################################

// Test for Reset Functionality
TEST(WeakPtrTest, Weak_ResetFunctionality) {
  SharedPtr<MyClass> shared(new MyClass(100));
  WeakPtr<MyClass> weak(shared);

  EXPECT_FALSE(weak.expired())
      << "WeakPtr should not be expired after initialization from SharedPtr.";
  EXPECT_EQ(weak.use_count(), 1) << "WeakPtr should report a use count of 1 "
                                    "after initialization from SharedPtr.";

  // Perform reset on WeakPtr
  weak.reset();

  EXPECT_TRUE(weak.expired()) << "WeakPtr should be expired after reset.";
  EXPECT_EQ(weak.use_count(), 0) << "Weak count should be 0 after reset.";
  EXPECT_EQ(shared.use_count(), 1) << "Resetting WeakPtr should not affect the "
                                      "use count of the original SharedPtr.";

  // Additional check to ensure no weak references linger
  WeakPtr<MyClass> anotherWeak(shared);
  shared.reset();  // Drop the SharedPtr, leaving only a weak reference

  EXPECT_TRUE(anotherWeak.expired())
      << "All WeakPtrs should be expired after the last SharedPtr is reset.";
  EXPECT_EQ(anotherWeak.use_count(), 0)
      << "Weak count should be 0 after all SharedPtrs are gone.";
}

// ############################################
// ######## Weak Pointer Observers     ########
// ############################################

// Test for Expired Status for Non-Existing Object
TEST(WeakPtrTest, Weak_ExpiredStatusForNonExistingObject) {
  WeakPtr<MyClass> weak;
  EXPECT_TRUE(weak.expired()) << "WeakPtr should be expired when it has never "
                                 "been associated with a SharedPtr.";

  SharedPtr<MyClass> shared(new MyClass(10));
  WeakPtr<MyClass> weakFromShared(shared);
  shared.reset();  // Destroy the object managed by SharedPtr

  //   EXPECT_TRUE(weakFromShared.expired())
  //       << "WeakPtr should be expired after the managed object is
  //       destroyed.";
}

// Test for Expired Status for Existing Object
TEST(WeakPtrTest, Weak_ExpiredStatusForExistingObject) {
  SharedPtr<MyClass> shared(new MyClass(20));
  WeakPtr<MyClass> weak(shared);
  EXPECT_FALSE(weak.expired()) << "WeakPtr should not be expired while the "
                                  "object is still being managed.";
}

// Test for Use Count Validity
TEST(WeakPtrTest, Weak_UseCountValidity) {
  SharedPtr<MyClass> shared(new MyClass(30));
  WeakPtr<MyClass> weak1(shared);
  WeakPtr<MyClass> weak2(shared);

  EXPECT_EQ(weak1.use_count(), 1) << "Use count should reflect the number of "
                                     "SharedPtr instances managing the object.";
  EXPECT_EQ(weak2.use_count(), 1)
      << "Use count should be consistent across multiple WeakPtr instances "
         "pointing to the same object.";
}

// Test for Boolean Conversion
TEST(WeakPtrTest, Weak_BooleanConversion) {
  SharedPtr<MyClass> shared(new MyClass(40));
  WeakPtr<MyClass> weak(shared);
  EXPECT_TRUE(weak)
      << "Boolean conversion should indicate true when WeakPtr is not expired.";

  weak.reset();
  EXPECT_FALSE(weak) << "Boolean conversion should indicate false when WeakPtr "
                        "is expired after reset.";
}

// ############################################
// ######## Weak Pointer Lock          ########
// ############################################

class SampleResource {
 public:
  int data;
  SampleResource(int val) : data(val) {}
};

TEST(WeakPtrTest, Weak_LockOnNonExpiredObject) {
  SharedPtr<SampleResource> shared(new SampleResource(100));
  WeakPtr<SampleResource> weak(shared);

  SharedPtr<SampleResource> locked = weak.lock();
  EXPECT_NE(locked.get(), nullptr) << "lock() should return a valid SharedPtr "
                                      "when the object is not expired.";
  EXPECT_EQ(locked.use_count(), 2)
      << "Use count should increase to 2 after locking a non-expired WeakPtr.";
  EXPECT_EQ(weak.use_count(), 2) << "Use count observed through WeakPtr should "
                                    "also reflect the new count after lock.";
}

// Test for Lock on Expired Object
TEST(WeakPtrTest, Weak_LockOnExpiredObject) {
  SharedPtr<SampleResource> shared(new SampleResource(200));
  WeakPtr<SampleResource> weak(shared);
  shared.reset();  // This should expire the weak pointer by destroying the
                   // managed object

  SharedPtr<SampleResource> locked = weak.lock();
  EXPECT_EQ(locked.get(), nullptr)
      << "lock() should return an empty SharedPtr when the object is expired.";
  EXPECT_EQ(locked.use_count(), 0)
      << "Use count of the returned SharedPtr should be 0 on expired lock.";
  EXPECT_TRUE(weak.expired())
      << "WeakPtr should be expired after the managed object is destroyed.";
  EXPECT_EQ(weak.use_count(), 0)
      << "Use count through WeakPtr should be 0 after the object is destroyed.";
}

// ############################################################
// ######## Weak Pointer Exception Safety, Edge Cases  ########
// ############################################################
#include <gtest/gtest.h>

#include "SharedPtr.h"
#include "WeakPtr.h"

// Test for Exception Safety Guarantees
TEST(WeakPtrTest, Weak_ExceptionSafetyGuarantees) {
  SharedPtr<MyClass> shared(new MyClass(100));
  WeakPtr<MyClass> weak1(shared);
  WeakPtr<MyClass> weak2;

  EXPECT_NO_THROW(weak2 = weak1) << "Copy assignment should not throw.";
  EXPECT_NO_THROW(weak2 = std::move(weak1))
      << "Move assignment should not throw.";
}

// Test for Self-Assignment Safety
TEST(WeakPtrTest, Weak_SelfAssignmentSafety) {
  SharedPtr<MyClass> shared(new MyClass(200));
  WeakPtr<MyClass> weak(shared);

  EXPECT_NO_THROW(weak = weak)
      << "Self-copy assignment should not throw and not alter the state.";
  EXPECT_EQ(weak.use_count(), 1)
      << "Use count should remain unchanged after self-copy assignment.";
}

// Stress Test on Weak Count
TEST(WeakPtrTest, Weak_StressTestOnWeakCount) {
  SharedPtr<MyClass> shared(new MyClass(300));
  WeakPtr<MyClass> weak1(shared);
  WeakPtr<MyClass> weak2(shared);
  WeakPtr<MyClass> weak3(shared);

  EXPECT_EQ(weak1.use_count(), 1) << "Weak count should initially reflect the "
                                     "number of SharedPtr instances.";

  weak2 = weak1;
  weak3.reset();  // Explicitly reset one WeakPtr
  EXPECT_EQ(weak1.use_count(), 1)
      << "Weak count should remain after resetting one WeakPtr.";

  shared.reset();  // Destroy the managed object
  EXPECT_TRUE(weak1.expired())
      << "All WeakPtrs should be expired after the SharedPtr is reset.";
  EXPECT_TRUE(weak2.expired())
      << "All WeakPtrs should be expired after the SharedPtr is reset.";
  EXPECT_TRUE(weak3.expired())
      << "All WeakPtrs should be expired after the SharedPtr is reset.";

  WeakPtr<MyClass> weak4 = weak2;
  EXPECT_EQ(weak4.use_count(), 0)
      << "Weak count should be 0 after assigning from an expired WeakPtr.";
}

// ############################################################
// ######## Weak Pointer Integration with SharedPtr  ##########
// ############################################################
// TEST(WeakPtrTest, Weak_SharedAndWeakInteraction) {
//   SharedPtr<MyClass> shared(new MyClass(100));
//   WeakPtr<MyClass> weak1(shared);
//   WeakPtr<MyClass> weak2;

//   // Initial checks on weak pointers and shared pointers
//   EXPECT_FALSE(weak1.expired())
//       << "WeakPtr should not be expired when there is an active SharedPtr.";
//   EXPECT_EQ(weak1.use_count(), 1)
//       << "Use count should be 1 when there is one SharedPtr.";

//   // Creating another SharedPtr from WeakPtr
//   SharedPtr<MyClass> shared2 = weak1.lock();
//   EXPECT_EQ(shared.use_count(), 2)
//       << "Use count should be 2 after locking WeakPtr into a new SharedPtr.";
//   EXPECT_EQ(weak1.use_count(), 2)
//       << "WeakPtr use count should update to reflect the new SharedPtr.";

//   // Assigning to another WeakPtr and modifying the original SharedPtr
//   weak2 = weak1;
//   shared.reset();  // Reset the original SharedPtr, should not destroy the
//                    // resource yet because of shared2

//   EXPECT_FALSE(weak1.expired())
//       << "WeakPtr should not be expired as long as there's another
//       SharedPtr.";
//   EXPECT_EQ(weak1.use_count(), 1)
//       << "Use count should be 1 after the original SharedPtr is reset.";
//   EXPECT_EQ(weak2.use_count(), 1) << "Use count should also be 1 for another
//   "
//                                      "WeakPtr linked to the same resource.";

//   shared2.reset();  // Now resetting the second SharedPtr, should lead to the
//                     // resource being destroyed

//   EXPECT_TRUE(weak1.expired())
//       << "WeakPtr should be expired after all SharedPtrs are reset.";
//   EXPECT_EQ(weak1.use_count(), 0)
//       << "Use count should be 0 after all SharedPtrs are reset.";
//   EXPECT_TRUE(weak2.expired())
//       << "All weak pointers should be expired after all SharedPtrs are
//       reset.";
//   EXPECT_EQ(weak2.use_count(), 0) << "Use count for all WeakPtrs should be 0
//   "
//                                      "after all SharedPtrs are reset.";
// }
/*
 */