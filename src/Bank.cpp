
#include "Bank.h"

#include <math.h>

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

bool Bank::transfer(Account& source, Account& destination,
                    const std::string& owner_fingerprint,
                    const std::string& CVV2, const std::string& password,
                    const std::string& exp_date, double amount) {
  // Authenticate owner's identity using fingerprint
  if (std::hash<std::string>{}(owner_fingerprint) !=
      source.get_owner()->get_hashed_fingerprint()) {
    return false;
  }

  // Verify credentials
  if (source.get_CVV2(const_cast<std::string&>(owner_fingerprint)) != CVV2 ||
      source.get_password(const_cast<std::string&>(owner_fingerprint)) !=
          password ||
      source.get_exp_date(const_cast<std::string&>(owner_fingerprint)) !=
          exp_date) {
    return false;
  }

  // Check if sufficient balance for transfer
  if (source.get_balance() < amount) {
    return false;
  }

  // Perform transfer operation
  source.balance = source.get_balance() - amount;
  destination.balance = destination.get_balance() + amount;
  return true;
}

bool Bank::take_loan(Account& account, const std::string& owner_fingerprint,
                     double amount) {
  // Authenticate owner's identity using fingerprint
  if (std::hash<std::string>{}(owner_fingerprint) !=
      account.get_owner()->get_hashed_fingerprint()) {
    return false;
  }

  // Calculate loan eligibility
  size_t rank = account.get_owner()->get_socioeconomic_rank();
  double max_loan = (10 * rank / 100.0) * bank_total_balance;

  if (amount > max_loan || amount <= 0) {
    return false;
  }

  // Update loan related variables
  bank_total_loan += amount;
  customer_2_unpaid_loan[const_cast<Person*>(account.get_owner())] += amount;

  // Deposit loan amount into account
  account.balance = account.get_balance() + amount;
  return true;
}

bool Bank::pay_loan(Account& account, double amount) {
  // Check if loan amount is valid
  if (amount <= 0 || amount > account.get_balance()) {
    return false;
  }

  // Calculate interest
  size_t rank = account.get_owner()->get_socioeconomic_rank();
  double interest = (amount * 10 / rank) / 100.0;

  // Deduct loan amount and interest from account balance
  account.balance = account.get_balance() - amount - interest;

  // Update loan related variables
  customer_2_paid_loan[const_cast<Person*>(account.get_owner())] += amount;
  customer_2_unpaid_loan[const_cast<Person*>(account.get_owner())] -= amount;

  // Check if socioeconomic rank upgrade is triggered
  double total_paid_loan =
      customer_2_paid_loan[const_cast<Person*>(account.get_owner())];
  size_t current_rank = account.get_owner()->get_socioeconomic_rank();
  if (total_paid_loan >= pow(10, current_rank)) {
    const_cast<Person*>(account.get_owner())
        ->set_socioeconomic_rank(current_rank + 1);
  }

  // Update bank total balance with interest
  bank_total_balance += interest;

  return true;
}

// Getters

const std::string& Bank::get_bank_name() const { return bank_name; }

size_t Bank::get_hashed_bank_fingerprint() const {
  return hashed_bank_fingerprint;
}

const std::vector<Person*>& Bank::get_bank_customers(
    std::string& bank_fingerprint) const {
  if (std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    throw std::invalid_argument("Bank fingerprint authentication failed.");
  }
  return bank_customers;
}

const std::vector<Account*>& Bank::get_bank_accounts(
    std::string& bank_fingerprint) const {
  if (std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    throw std::invalid_argument("Bank fingerprint authentication failed.");
  }
  return bank_accounts;
}

const std::map<Account*, Person*>& Bank::get_account_2_customer_map(
    std::string& bank_fingerprint) const {
  if (std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    throw std::invalid_argument("Bank fingerprint authentication failed.");
  }
  return account_2_customer;
}

const std::map<Person*, std::vector<Account*>>&
Bank::get_customer_2_accounts_map(std::string& bank_fingerprint) const {
  if (std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    throw std::invalid_argument("Bank fingerprint authentication failed.");
  }
  return customer_2_accounts;
}

const std::map<Person*, double>& Bank::get_customer_2_paid_loan_map(
    std::string& bank_fingerprint) const {
  if (std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    throw std::invalid_argument("Bank fingerprint authentication failed.");
  }
  return customer_2_paid_loan;
}

const std::map<Person*, double>& Bank::get_customer_2_unpaid_loan_map(
    std::string& bank_fingerprint) const {
  if (std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    throw std::invalid_argument("Bank fingerprint authentication failed.");
  }
  return customer_2_unpaid_loan;
}

double Bank::get_bank_total_balance(std::string& bank_fingerprint) const {
  if (std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    throw std::invalid_argument("Bank fingerprint authentication failed.");
  }
  return bank_total_balance;
}

double Bank::get_bank_total_loan(std::string& bank_fingerprint) const {
  if (std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    throw std::invalid_argument("Bank fingerprint authentication failed.");
  }
  return bank_total_loan;
}

// Account Setters

bool Bank::set_owner(Account& account, const Person* new_owner,
                     std::string& owner_fingerprint,
                     std::string& bank_fingerprint) {
  // Authenticate owner and bank's identity using fingerprints
  if (std::hash<std::string>{}(owner_fingerprint) !=
          account.get_owner()->get_hashed_fingerprint() ||
      std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    return false;
  }

  // Update account's owner
  account.owner = const_cast<Person*>(new_owner);
  return true;
}

bool Bank::set_account_status(Account& account, bool status,
                              std::string& bank_fingerprint) {
  // Authenticate bank's identity using fingerprint
  if (std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    return false;
  }

  // Update account status
  account.account_status = status;
  return true;
}

bool Bank::set_exp_date(Account& account, std::string& exp_date,
                        std::string& bank_fingerprint) {
  // Authenticate bank's identity using fingerprint
  if (std::hash<std::string>{}(bank_fingerprint) != hashed_bank_fingerprint) {
    return false;
  }

  // Update account's expiration date
  account.exp_date = exp_date;
  return true;
}