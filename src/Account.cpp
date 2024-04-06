#include "Account.h"

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