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
  for (int i = 0; i < 4; ++i) {
    cvv2 += std::to_string(distrib(gen));
  }
  return cvv2;
}

// Generate a random expiration date (MM/YY)
std::string generate_exp_date() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib_month(1, 12);
  std::uniform_int_distribution<int> distrib_year(20, 30);

  int month = distrib_month(gen);
  int year = distrib_year(gen);

  return std::to_string(year) + "-" +
         (month < 10 ? "0" + std::to_string(month) : std::to_string(month));
}