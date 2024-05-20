#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

class Cinnamon : public Ingredient {
 public:
  Cinnamon(size_t units) : Ingredient{5.0, units} { this->name = "Cinnamon"; }

  double get_price_unit() override { return price_unit; }
  size_t get_units() override { return units; }
  std::string get_name() override { return this->name; }
  double price() override { return price_unit * units; }
};

class Chocolate : public Ingredient {
 public:
  Chocolate(size_t units) : Ingredient{5, units} { this->name = "Chocolate"; }

  double get_price_unit() override { return price_unit; }
  size_t get_units() override { return units; }
  std::string get_name() override { return this->name; }
  double price() override { return price_unit * units; }
};

class Sugar : public Ingredient {
 public:
  Sugar(size_t units) : Ingredient{1, units} { this->name = "Sugar"; }

  double get_price_unit() override { return price_unit; }
  size_t get_units() override { return units; }
  std::string get_name() override { return this->name; }
  double price() override { return price_unit * units; }
};

class Cookie : public Ingredient {
 public:
  Cookie(size_t units) : Ingredient{10, units} { this->name = "Cookie"; }

  double get_price_unit() override { return price_unit; }
  size_t get_units() override { return units; }
  std::string get_name() override { return this->name; }
  double price() override { return price_unit * units; }
};

class Espresso : public Ingredient {
 public:
  Espresso(size_t units) : Ingredient{15, units} { this->name = "Espresso"; }

  double get_price_unit() override { return price_unit; }
  size_t get_units() override { return units; }
  std::string get_name() override { return this->name; }
  double price() override { return price_unit * units; }
};

class Milk : public Ingredient {
 public:
  Milk(size_t units) : Ingredient{10, units} { this->name = "Milk"; }

  double get_price_unit() override { return price_unit; }
  size_t get_units() override { return units; }
  std::string get_name() override { return this->name; }
  double price() override { return price_unit * units; }
};

class MilkFoam : public Ingredient {
 public:
  MilkFoam(size_t units) : Ingredient{5, units} { this->name = "MilkFoam"; }

  double get_price_unit() override { return price_unit; }
  size_t get_units() override { return units; }
  std::string get_name() override { return this->name; }
  double price() override { return price_unit * units; }
};

class Water : public Ingredient {
 public:
  Water(size_t units) : Ingredient{1, units} { this->name = "Water"; }

  double get_price_unit() override { return price_unit; }
  size_t get_units() override { return units; }
  std::string get_name() override { return this->name; }
  double price() override { return price_unit * units; }
};

#endif  // SUB_INGREDIENTS_H
