#include "Person.h"

#include <fstream>
#include <iostream>
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

// Getters
std::string Person::get_name() const { return name; }

size_t Person::get_age() const { return age; }

std::string Person::get_gender() const { return gender; }

size_t Person::get_hashed_fingerprint() const { return hashed_fingerprint; }

size_t Person::get_socioeconomic_rank() const { return socioeconomic_rank; }

bool Person::get_is_alive() const { return is_alive; }

// Setters
bool Person::set_age(size_t age) {
  this->age = age;
  return true;
}

bool Person::set_socioeconomic_rank(size_t rank) {
  if (rank < 1 || rank > 10) {
    throw std::invalid_argument(
        "The socioeconomic rank is an integer value ranging from 1 to 10.");
  }
  this->socioeconomic_rank = rank;
  return true;
}

bool Person::set_is_alive(bool is_alive) {
  this->is_alive = is_alive;
  return true;
}

// Outputs person information
void Person::get_info(std::optional<std::string> file_name) const {
  if (file_name.has_value()) {
    std::ofstream output(file_name.value());
    output << "Name: " << name << std::endl;
    output << "Age: " << age << std::endl;
    output << "Gender: " << gender << std::endl;
    output << "Hashed Fingerprint: " << hashed_fingerprint << std::endl;
    output << "Socioeconomic Rank: " << socioeconomic_rank << std::endl;
    output << "Is Alive: " << (is_alive ? "Yes" : "No") << std::endl;
    output.close();
  } else {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Gender: " << gender << std::endl;
    std::cout << "Hashed Fingerprint: " << hashed_fingerprint << std::endl;
    std::cout << "Socioeconomic Rank: " << socioeconomic_rank << std::endl;
    std::cout << "Is Alive: " << (is_alive ? "Yes" : "No") << std::endl;
  }
}