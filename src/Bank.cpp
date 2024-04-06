
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

bool Bank::delete_account(Account& account,
                          const std::string& owner_fingerprint) {
  // Authenticate owner's identity using fingerprint
  if (std::hash<std::string>{}(owner_fingerprint) !=
      account.get_owner()->get_hashed_fingerprint()) {
    return false;
  }

  // Remove account from bank data structures
  auto it = std::find(bank_accounts.begin(), bank_accounts.end(), &account);
  if (it != bank_accounts.end()) {
    bank_accounts.erase(it);
    account_2_customer.erase(&account);
    auto& accounts_of_owner =
        customer_2_accounts[const_cast<Person*>(account.get_owner())];
    accounts_of_owner.erase(std::remove(accounts_of_owner.begin(),
                                        accounts_of_owner.end(), &account),
                            accounts_of_owner.end());
    delete &account;
    return true;
  }
  return false;
}

bool Bank::delete_customer(Person& owner,
                           const std::string& owner_fingerprint) {
  // Authenticate owner's identity using fingerprint
  if (std::hash<std::string>{}(owner_fingerprint) !=
      owner.get_hashed_fingerprint()) {
    return false;
  }

  // Remove customer and associated accounts from bank data structures
  auto it = std::find(bank_customers.begin(), bank_customers.end(), &owner);
  if (it != bank_customers.end()) {
    for (auto& account : customer_2_accounts[&owner]) {
      delete_account(*account, owner_fingerprint);
    }
    bank_customers.erase(it);
    delete &owner;
    return true;
  }
  return false;
}

bool Bank::deposit(Account& account, const std::string& owner_fingerprint,
                   double amount) {
  // Authenticate owner's identity using fingerprint
  if (std::hash<std::string>{}(owner_fingerprint) !=
      account.get_owner()->get_hashed_fingerprint()) {
    return false;
  }

  // Perform deposit operation
  account.balance = account.get_balance() + amount;
  bank_total_balance += amount;
  return true;
}

bool Bank::withdraw(Account& account, const std::string& owner_fingerprint,
                    double amount) {
  // Authenticate owner's identity using fingerprint
  if (std::hash<std::string>{}(owner_fingerprint) !=
      account.get_owner()->get_hashed_fingerprint()) {
    return false;
  }

  // Check if sufficient balance
  if (account.get_balance() < amount) {
    return false;
  }

  // Perform withdrawal operation
  account.balance = account.get_balance() - amount;
  bank_total_balance -= amount;
  return true;
}
