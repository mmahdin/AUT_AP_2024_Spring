#include "Account.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Bank.h"
#include "Person.h"
#include "Utils.h"

// Constructor with owner, bank, and password
Account::Account(const Person* const owner, const Bank* const bank,
                 std::string& password)
    : owner(const_cast<Person*>(owner)),
      bank(bank),
      account_number(generate_account_number()),
      balance(0),
      account_status(true),
      CVV2(generate_CVV2()),
      password(password),
      exp_date(generate_exp_date()) {
  // Ensure owner and bank pointers are valid
  if (!owner || !bank) {
    throw std::invalid_argument("Owner and bank must be valid pointers.");
  }
}

// Getters
const Person* Account::get_owner() const { return owner; }

double Account::get_balance() const { return balance; }

std::string Account::get_account_number() const { return account_number; }

bool Account::get_status() const { return account_status; }

// Getters requiring owner's fingerprint for authentication
std::string Account::get_CVV2(std::string& owner_fingerprint) const {
  if (std::hash<std::string>{}(owner_fingerprint) !=
      owner->get_hashed_fingerprint()) {
    throw std::invalid_argument("Fingerprint authentication failed.");
  }
  return CVV2;
}

std::string Account::get_password(std::string& owner_fingerprint) const {
  if (std::hash<std::string>{}(owner_fingerprint) !=
      owner->get_hashed_fingerprint()) {
    throw std::invalid_argument("Fingerprint authentication failed.");
  }
  return password;
}

std::string Account::get_exp_date(std::string& owner_fingerprint) const {
  if (std::hash<std::string>{}(owner_fingerprint) !=
      owner->get_hashed_fingerprint()) {
    throw std::invalid_argument("Fingerprint authentication failed.");
  }
  return exp_date;
}

// Setters requiring owner's fingerprint for authentication
bool Account::set_password(std::string& new_password,
                           std::string& owner_fingerprint) {
  if (std::hash<std::string>{}(owner_fingerprint) !=
      owner->get_hashed_fingerprint()) {
    return false;
  }
  password = new_password;
  return true;
}

// Spaceship operator for Account comparison
std::strong_ordering Account::operator<=>(const Account& other) const {
  // Compare based on account_number
  return account_number <=> other.account_number;
}

// Outputs account information
void Account::get_info(std::optional<std::string> file_name) const {
  if (file_name.has_value()) {
    std::ofstream output(file_name.value());
    output << "Account Information:" << std::endl;
    output << "Owner: " << owner->get_name() << std::endl;
    // std::cout << "Bank: " << bank->get_name() << std::endl;
    output << "Account Number: " << account_number << std::endl;
    output << "Balance: " << balance << std::endl;
    output << "Status: " << (account_status ? "Active" : "Inactive")
           << std::endl;
    output.close();
  } else {
    std::cout << "Account Information:" << std::endl;
    std::cout << "Owner: " << owner->get_name() << std::endl;
    // std::cout << "Bank: " << bank->get_name() << std::endl;
    std::cout << "Account Number: " << account_number << std::endl;
    std::cout << "Balance: " << balance << std::endl;
    std::cout << "Status: " << (account_status ? "Active" : "Inactive")
              << std::endl;
  }
}