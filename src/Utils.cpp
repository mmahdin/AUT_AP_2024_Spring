#include "Utils.h"

// Generate a random 16-digit account number
std::string generate_account_number() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(0, 9);

  std::string acc_number = "";
  for (int i = 0; i < 16; ++i) {
    acc_number += std::to_string(distrib(gen));
  }
  return acc_number;
}

// Generate a random 3-digit CVV2
std::string generate_CVV2() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(0, 9);

  std::string cvv2 = "";
  for (int i = 0; i < 3; ++i) {
    cvv2 += std::to_string(distrib(gen));
  }
  return cvv2;
}