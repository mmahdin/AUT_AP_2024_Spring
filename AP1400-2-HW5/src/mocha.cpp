#include "mocha.h"

Mocha::Mocha() : cnt{new unsigned{1}} {
  name = "Mocha";
  ingredients.push_back(new Espresso{2});
  ingredients.push_back(new Milk{2});
  ingredients.push_back(new MilkFoam{1});
  ingredients.push_back(new Chocolate{1});
}

Mocha::Mocha(const Mocha& cap)
    : cnt{cap.cnt}, EspressoBased(cap), side_items(cap.side_items) {
  (*cnt)++;
}

Mocha::~Mocha() { release(); }

void Mocha::operator=(const Mocha& cap) {
  if (this != &cap) {
    EspressoBased::operator=(cap);
    cnt = cap.cnt;
    (*cnt)++;
    side_items = cap.side_items;
  }
}

std::string Mocha::get_name() { return name; }

double Mocha::price() {
  double total = 0.0;
  for (const auto& ingredient : ingredients) {
    total += ingredient->price();
  }
  for (const auto& side : side_items) {
    total += side->price();
  }
  return total;
}

void Mocha::add_side_item(Ingredient* side) { side_items.push_back(side); }

std::vector<Ingredient*>& Mocha::get_side_items() { return side_items; }