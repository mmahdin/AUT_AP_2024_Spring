#include "Bank.h"

#include <functional>
#include <iostream>
#include <stdexcept>

// Constructor with bank name and security fingerprint
Bank::Bank(const std::string& bank_name, const std::string& bank_fingerprint)
    : bank_name(bank_name),
      hashed_bank_fingerprint(std::hash<std::string>{}(bank_fingerprint)),
      bank_total_balance(0),
      bank_total_loan(0) {}
