
#include "Bank.h"

#include <functional>
#include <iostream>
#include <stdexcept>

#include "Account.h"
#include "Person.h"

// Constructor with bank name and security fingerprint
Bank::Bank(const std::string& bank_name, const std::string& bank_fingerprint)
    : bank_name(bank_name),
      hashed_bank_fingerprint(std::hash<std::string>{}(bank_fingerprint)),
      bank_total_balance(0),
      bank_total_loan(0) {}

// Destructor
Bank::~Bank() {
  // Clean up dynamically allocated memory
  for (auto& customer : bank_customers) {
    delete customer;
  }
  for (auto& account : bank_accounts) {
    delete account;
  }
}