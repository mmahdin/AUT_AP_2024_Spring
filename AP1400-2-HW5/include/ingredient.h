#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
 public:
  double get_price_unit();
  size_t get_units();
  std::string get_name();

  double price();

 protected:
  Ingredient(double price_unit, size_t units);

  double price_unit;
  size_t units;
  std::string name;
};

#endif  // INGREDIENT_H