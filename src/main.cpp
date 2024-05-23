#include <gtest/gtest.h>

#include <iostream>

#include "BaseControlBlock.h"
#include "SharedControlBlock.h"
#include "SharedPtr.h"
#include "WeakControlBlock.h"
#include "WeakPtr.h"

class SelfReferentialClass {
 public:
  SharedPtr<SelfReferentialClass> self;
};

int main(int argc, char** argv) {
  if (false)  // Set to false to run unit-tests
  {
    SharedPtr<SelfReferentialClass> ptr1(new SelfReferentialClass());
    std::cout << (*ptr1).self.get() << std::endl;
    ptr1->self = ptr1;  // Creating a circular reference
    std::cout << ptr1.get() << std::endl;
    std::cout << (*ptr1).self.get() << std::endl;
    SharedPtr<SelfReferentialClass> ptr2 = ptr1;
    std::cout << ptr1.use_count() << std::endl;
    // Debug section: Place your debugging code here
  } else {
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
