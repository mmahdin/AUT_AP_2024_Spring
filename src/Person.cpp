#include "Person.h"

#include <stdexcept>

#include "Utils.h"

// Constructor with personal attributes
Person::Person(std::string &name, size_t age, std::string &gender,
               std::string &fingerprint, size_t socioeconomic_rank,
               bool is_alive)
    : name(name),
      age(age),
      gender(gender),
      hashed_fingerprint(std::hash<std::string>{}(
          fingerprint)),  // creates a temporary instance
      socioeconomic_rank(socioeconomic_rank),
      is_alive(is_alive) {
  // Validate gender
  if (gender != "Female" && gender != "Male")
    throw std::invalid_argument("Gender must be Male or Female.");

  // Validate range of socioeconomic rank
  if (socioeconomic_rank < 1 && socioeconomic_rank > 10)
    throw std::invalid_argument(
        "The socioeconomic rank is an integer value ranging from 1 to 10.");
}

// Spaceship operator for Person comparison
std::strong_ordering Person::operator<=>(const Person &other) const {
  return hashed_fingerprint <=> other.hashed_fingerprint;
}
