#include "espresso_based.h"

EspressoBased::EspressoBased() {}

EspressoBased::EspressoBased(const EspressoBased& esp)
    : ingredients(esp.ingredients), name(esp.name) {}

void EspressoBased::operator=(const EspressoBased& esp) {
  if (this != &esp) {
    ingredients = esp.ingredients;
    name = esp.name;
  }
}

EspressoBased::~EspressoBased() {}

std::vector<Ingredient*>& EspressoBased::get_ingredients() {
  return ingredients;
}