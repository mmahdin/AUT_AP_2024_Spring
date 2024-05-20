#include <gtest/gtest.h>

#include <iostream>

#include "shared_ptr.h"
#include "unique_ptr.h"

int main(int argc, char** argv) {
  if (false)  // make false to run unit-tests
  {
    UniquePtr<int> mahdi{make_unique<int>(10)};

    // code below rise the compiler error
    // UniquePtr<int> javad{mahdi};

    // code below rise the compiler error
    // UniquePtr<int> javad{};
    // javad = mahdi;

    std::cout << *mahdi << std::endl;

    UniquePtr<std::string> javad{new std::string{"hello"}};
    std::cout << javad->length() << std::endl;

    std::cout << *javad << std::endl;
    javad.reset(new std::string{"javad"});
    std::cout << *javad << std::endl;

    UniquePtr<double> ptr{new double{1.567}};
    double* tmp{ptr.release()};
    std::cout << *tmp << std::endl;  // output: 1.567
    delete tmp;                      // manual deletion

    // std::cout << *mahdi << std::endl;
    // *mahdi = 42;
    // std::cout << *mahdi << std::endl;
    // debug section

    SharedPtr<int> ptr1{new int{10}};
    std::cout << ptr1.getn() << std::endl;
    SharedPtr<int> ptr2{ptr1};
    std::cout << ptr2.getn() << std::endl;

    SharedPtr<int> ptr3{ptr1};
    std::cout << ptr3.getn() << std::endl;
    SharedPtr<int> ptr4{ptr2};
    std::cout << ptr4.getn() << std::endl;
    ptr3 = ptr4;
    std::cout << ptr3.getn() << std::endl;
    std::cout << ptr4.getn() << std::endl;

    SharedPtr<int> ptr5{new int{10}};
    std::cout << *ptr5 << std::endl;  // output: 10

    SharedPtr<std::string> ptr6{new std::string{"hello"}};
    std::cout << ptr6->length() << std::endl;  // output: 5

    std::cout << "reset test " << std::endl;
    ptr6.reset();

    SharedPtr<std::string> ptr7{new std::string{"hello"}};
    std::cout << *ptr7.get() << std::endl;
    ptr7.reset(new std::string{"salam"});
    std::cout << *ptr7.get() << std::endl;

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
