
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

Account* Bank::create_account(Person& owner,
                              const std::string& owner_fingerprint,
                              std::string password) {
  // Authenticate owner's identity using fingerprint
  if (std::hash<std::string>{}(owner_fingerprint) !=
      owner.get_hashed_fingerprint()) {
    throw std::invalid_argument("Owner's fingerprint authentication failed.");
  }

  // Create new account
  Account* new_account = new Account(&owner, this, password);

  // Update bank data structures
  bank_accounts.push_back(new_account);
  account_2_customer[new_account] = &owner;
  customer_2_accounts[&owner].push_back(new_account);

  return new_account;
}