#include "cappuccino.h"

Cappuccino::Cappuccino() : cnt{new unsigned{1}} {
  name = "Cappuccino";
  ingredients.push_back(new Espresso{2});
  ingredients.push_back(new Milk{2});
  ingredients.push_back(new MilkFoam{1});
}

Cappuccino::Cappuccino(const Cappuccino& cap)
    : cnt{cap.cnt}, EspressoBased(cap), side_items(cap.side_items) {
  (*cnt)++;
}

Cappuccino::~Cappuccino() { release(); }

void Cappuccino::operator=(const Cappuccino& cap) {
  if (this != &cap) {
    EspressoBased::operator=(cap);
    cnt = cap.cnt;
    (*cnt)++;
    side_items = cap.side_items;
  }
}

std::string Cappuccino::get_name() { return name; }

double Cappuccino::price() {
  double total = 0.0;
  for (const auto& ingredient : ingredients) {
    total += ingredient->price();
  }
  for (const auto& side : side_items) {
    total += side->price();
  }
  return total;
}

void Cappuccino::add_side_item(Ingredient* side) { side_items.push_back(side); }

std::vector<Ingredient*>& Cappuccino::get_side_items() { return side_items; }